/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:52:57 by agrouard          #+#    #+#             */
/*   Updated: 2018/12/12 09:53:19 by agrouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"

#include <unistd.h>
#include <signal.h>

int		job_fg(t_shell *shell, t_job *job, int cont)
{
	int		ret;

	if (!shell->is_subshell)
		tcsetpgrp(0, job->pgid);
	job_bg(job, cont);
	job->async = 0;
	ret = wait_job(shell, job);
	if (!shell->is_subshell)
		tcsetpgrp(0, getpid());
	return (ret);
}

void	job_bg(t_job *job, int cont)
{
	t_proc	*p;

	job->state = JOB_RUNNING;
	job->async = 1;
	if (cont && kill(-job->pgid, SIGCONT) < 0)
		ft_putendl_fd(EXEC_NAME": failed to send SIGCONT to job", 2);
	p = job->proc;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
}

int		job_is_stopped(t_job *j)
{
	t_proc *p;

	if (j->state == JOB_STOPPED || j->state == JOB_DONE)
		return (1);
	p = j->proc;
	while (p)
	{
		if (p->pid && !p->done && !p->stopped)
			return (0);
		p = p->next;
	}
	j->state = JOB_STOPPED;
	return (1);
}

int		job_is_done(t_job *j)
{
	t_proc *p;

	if (j->state == JOB_DONE)
		return (1);
	p = j->proc;
	while (p)
	{
		if (p->pid && !p->done)
			return (0);
		p = p->next;
	}
	j->state = JOB_DONE;
	return (1);
}
