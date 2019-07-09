/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:52:57 by agrouard          #+#    #+#             */
/*   Updated: 2019/07/09 10:20:01 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"
#include "sig_msg.h"

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

static const t_sig_msg	g_signal_msg[] = {
	{.sig = SIGHUP, .msg = "Hangup"},
	{.sig = SIGINT, .msg = ""},
	{.sig = SIGQUIT, .msg = "Quit"},
	{.sig = SIGILL, .msg = "Illegal instruction"},
	{.sig = SIGTRAP, .msg = "BPT trace/trap"},
	{.sig = SIGABRT, .msg = "Aborted"},
	{.sig = SIGBUS, .msg = "Bus error"},
	{.sig = SIGFPE, .msg = "Floating point exception"},
	{.sig = SIGKILL, .msg = "Killed"},
	{.sig = SIGUSR1, .msg = "User defined signal 1"},
	{.sig = SIGSEGV, .msg = "Segmentation fault"},
	{.sig = SIGUSR2, .msg = "User defined signal 2"},
	{.sig = SIGPIPE, .msg = "Broken pipe"},
	{.sig = SIGALRM, .msg = "Alarm clock"},
	{.sig = SIGTERM, .msg = "Terminated"},
	{.sig = SIGSTOP, .msg = "Signal"},
	{.sig = SIGTSTP, .msg = ""},
	{.sig = SIGTTIN, .msg = "tty input"},
	{.sig = SIGTTOU, .msg = "tty output"},
	{.sig = SIGURG, .msg = ""},
	{.sig = SIGXCPU, .msg = "Cpu time limit exceeded"},
	{.sig = SIGXFSZ, .msg = "Filesize limit exceeded"},
	{.sig = SIGVTALRM, .msg = "Virtual timer expired"},
	{.sig = SIGPROF, .msg = "Profiling timer expired"},
	{.sig = SIGIO, .msg = "I/O possible"},
	{.sig = SIGSYS, .msg = "Bad system call"},
	{.msg = NULL}
};


static void	print_job_infos(t_shell *shell, t_job *job, int fd)
{
	ft_dprintf(fd, "[%d]", job->index);
	if (job == shell->curr)
		ft_putchar_fd('+', fd);
	else if (job == shell->prev)
		ft_putchar_fd('-', fd);
	else
		ft_putchar_fd(' ', fd);
	ft_putchar_fd(' ', fd);
}

static const char	*get_sig_msg(int sig)
{
	size_t	i;

	i = 0;
	while (g_signal_msg[i].msg)
	{
		if (g_signal_msg[i].sig == sig)
			return g_signal_msg[i].msg;
		i++;
	}
	return ("");
}

static void	print_job_state(t_job *job, int fd)
{
	static const char	*status[] = {"None", "Running", "Stopped", "Done"};
	int			s;

	s = job->last->status;
	if (WIFSIGNALED(s))
		ft_dprintf(fd, "%s%s", get_sig_msg(WTERMSIG(s)),
			WCOREDUMP(s) ? "\t(core dumped)" : "");
	else
	{
		ft_dprintf(fd, " %s", status[job->state]);
		if (job->state == JOB_DONE && job->last->ret)
			ft_dprintf(fd, "(%d)", job->last->ret);
		if (WIFSTOPPED(s) && *get_sig_msg(WSTOPSIG(s)))
			ft_dprintf(fd, "(%s)", get_sig_msg(WSTOPSIG(s)));
	}
}

static void	print_pipeline(t_job *job, int fd)
{
	t_proc		*p;

	p = job->proc;
	ft_putstr(p->name);
	while (p->next)
	{
		p = p->next;
		ft_dprintf(fd, "| %s", p->name);
	}
}

t_job		*report_job(t_shell *shell, t_job *job, int opts, int fd)
{
	t_job		*next;

	next = job->next;
	if (opts & 1)
		print_job_infos(shell, job, fd);
	if (opts & 2)
		ft_dprintf(fd, "%d", job->pgid);
	if (opts & 4)
		print_job_state(job, fd);
	if (opts & 4 && opts & 8)
		ft_dprintf(fd, "\t\t");
	if (opts & 8)
	{
		print_pipeline(job, fd);
		if (job->state == JOB_DONE)
			free_job(shell, job);
		else
			job->notified = 1;
	}
	ft_putchar_fd('\n', fd);
	return (next);
}
