/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:52:57 by agrouard          #+#    #+#             */
/*   Updated: 2019/07/07 01:40:57 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"
#include "sig_msg.h"

#include <unistd.h>
#include <signal.h>

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


static void	print_job_infos(t_shell *shell, t_job *job)
{
	ft_printf("[%d]", job->index);
	if (job == shell->curr)
		ft_putchar('+');
	else if (job == shell->prev)
		ft_putchar('-');
	else
		ft_putchar(' ');
	ft_putchar(' ');
}

static void	print_msg_sig(int ret)
{
	size_t	i;

	i = 0;
	while (g_signal_msg[i].msg != NULL)
	{
		if (g_signal_msg[i].rtn == ret - 128)
			ft_dprintf(2, "%s%s\n", g_signal_msg[i].msg);
		i++;
	}
}

static void	print_job_state(t_job *job)
{
	static const char	*status[] = {"None", "Running", "Stopped", "Done"};

	ft_printf(" %s", status[job->state]);
	if (job->state == JOB_DONE && job->last->ret)
		ft_printf("(%d)", job->last->ret);
	if (job->state == JOB_STOPPED)
		print_msg_sig(job->last->ret);
}

static void	print_pipeline(t_job *job)
{
	t_proc		*p;

	p = job->proc;
	ft_putstr(p->name);
	while (p->next)
	{
		p = p->next;
		ft_putstr(" | ");
		ft_putstr(p->name);
	}
}

t_job		*report_job(t_shell *shell, t_job *job, int opts)
{
	t_job		*next;

	next = job->next;
	if (opts & 1)
		print_job_infos(shell, job);
	if (opts & 2)
		ft_printf("%d", job->pgid);
	if (opts & 4)
		print_job_state(job);
	if (opts & 4 && opts & 8)
		ft_printf("\t\t");
	if (opts & 8)
	{
		print_pipeline(job);
		if (job->state == JOB_DONE)
			free_job(shell, job);
		else
			job->notified = 1;
	}
	ft_putchar('\n');
	return (next);
}
