/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <gchainet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 15:49:17 by gchainet          #+#    #+#             */
/*   Updated: 2019/03/30 20:20:36 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"
#include "sig_msg.h"

static const t_sig_msg	g_signal_msg[] = {
	{.sig = SIGHUP, .rtn = 129, .msg = "Hangup: 1"},
	{.sig = SIGINT, .rtn = 130, .msg = ""},
	{.sig = SIGQUIT, .rtn = 131, .msg = "Quit: 3"},
	{.sig = SIGILL, .rtn = 132, .msg = "Illegal instruction: 4"},
	{.sig = SIGTRAP, .rtn = 133, .msg = "Trace/BPT trap: 5"},
	{.sig = SIGABRT, .rtn = 134, .msg = "Abort trap: 6"},
	{.sig = SIGFPE, .rtn = 136, .msg = "Floating point exception: 8"},
	{.sig = SIGKILL, .rtn = 137, .msg = "Killed: 9"},
	{.sig = SIGBUS, .rtn = 138, .msg = "Bus error: 10"},
	{.sig = SIGSEGV, .rtn = 139, .msg = "Segmentation fault: 11"},
	{.sig = SIGSYS, .rtn = 140, .msg = "Bad system call: 12"},
	{.sig = SIGPIPE, .rtn = 141, .msg = ""},
	{.sig = SIGALRM, .rtn = 142, .msg = "Alarm clock: 14"},
	{.sig = SIGTERM, .rtn = 143, .msg = "Terminated: 15"},
	{.sig = SIGURG, .rtn = 0, .msg = ""},
	{.sig = SIGXCPU, .rtn = 152, .msg = "Cputime limit exceeded: 24"},
	{.sig = SIGXFSZ, .rtn = 153, .msg = "Filesize limit exceeded: 25"},
	{.sig = SIGVTALRM, .rtn = 142, .msg = "Alarm clock: 14"},
	{.sig = SIGPROF, .rtn = 155, .msg = "Profiling timer expired: 27"},
	{.sig = SIGUSR1, .rtn = 158, .msg = "User defined signal 1: 30"},
	{.sig = SIGUSR2, .rtn = 159, .msg = "User defined signal 2: 31"},
	{.msg = NULL}
};

static int	print_crash_signal(int status)
{
	size_t	i;

	if (WIFSIGNALED(status))
	{
		i = 0;
		while (g_signal_msg[i].msg != NULL)
		{
			if (g_signal_msg[i].sig == WTERMSIG(status))
			{
				ft_putstr(g_signal_msg[i].msg);
				ft_putendl(WCOREDUMP(status) ? " (core dumped)" : "");
				return (g_signal_msg[i].rtn);
			}
			i++;
		}
	}
	return (0);
}

static int	is_over(t_ast *ast)
{
	if (ast)
	{
		if (ast->pid == -1)
			return (is_over(ast->left) && is_over(ast->right));
		return (0);
	}
	return (1);
}

static int	set_process_as_finished(t_ast *ast, pid_t pid, int status,
									int crash)
{
	if (ast)
	{
		if (ast->pid == pid)
		{
			ast->pid = -1;
			ast->ret = WEXITSTATUS(status);
			if (crash != 0)
				ast->ret = crash;
			return (1);
		}
		else
		{
			if (!set_process_as_finished(ast->left, pid, status, crash))
				set_process_as_finished(ast->right, pid, status, crash);
		}
	}
	return (0);
}

static void	do_wait(t_ast *ast)
{
	int		status;
	pid_t	pid;
	int		crash;

	if ((pid = waitpid(0, &status, 0)) > 0)
	{
		crash = print_crash_signal(status);
		if (WIFEXITED(status) || WIFSIGNALED(status))
			set_process_as_finished(ast, pid, status, crash);
	}
}

int			wait_loop(t_ast *ast)
{
	signal(SIGINT, SIG_IGN);
	reset_terminal_mode(NULL);
	while (!is_over(ast))
		do_wait(ast);
	signal(SIGINT, prompt_signal_handler);
	return (0);
}
