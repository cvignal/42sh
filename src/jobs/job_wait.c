/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:52:57 by agrouard          #+#    #+#             */
/*   Updated: 2018/12/12 09:56:37 by agrouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"
#include <sys/wait.h>

static t_proc	*find_proc(t_shell *shell, pid_t pid)
{
	t_job	*j;
	t_proc	*p;

	j = shell->jobs;
	while (j)
	{
		p = j->proc;
		while (p)
		{
			if (p->pid == pid)
				return (p);
			p = p->next;
		}
		j = j->next;
	}
	return (NULL);
}

void			update_proc(t_shell *shell, pid_t pid, int status)
{
	t_proc	*p;

	if (!(p = find_proc(shell, pid)))
		return ;
	if (WIFEXITED(status))
	{
		p->done = 1;
		p->ret = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
	{
		p->done = 1;
		p->ret = 128 + WTERMSIG(status);
	}
	else if (WIFSTOPPED(status))
	{
		p->stopped = 1;
		p->ret = 128 + WSTOPSIG(status);
	}
}

int				wait_job(t_shell *shell, t_job *job)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	while (!job_is_stopped(job))
	{
		if ((pid = waitpid(-1, &status, WUNTRACED)) < 0)
			break ;
		ft_printf("%d\r\n\r\n", pid);
		update_proc(shell, pid, status);
	}
	while ((pid = waitpid(-1, &status, WUNTRACED | WNOHANG)) > 0)
		update_proc(shell, pid, status);
	status = job->last->ret;
	if (job_is_done(job))
		free_job(shell, job);
	else if (job->state == JOB_STOPPED)
		report_job(shell, job, 0);
	job = shell->jobs;
	while (job)
	{
		if (job_is_done(job))
			job = report_job(shell, job, 0);
		else
			job = job->next;
	}
	return (status);
}

void			update_jobs(t_shell *shell)
{
	pid_t	pid;
	int		status;
	t_job	*j;

	while ((pid = waitpid(-1, &status, WUNTRACED | WNOHANG)) > 0)
		update_proc(shell, pid, status);
	j = shell->jobs;
	shell->curr = NULL;
	shell->prev = NULL;
	while (j)
	{
		job_is_done(j);
		if (j->state == JOB_STOPPED || !shell->curr)
		{
			shell->prev = shell->curr;
			shell->curr = j;
		}
		else if (!shell->prev)
			shell->prev = j;
		j = j->next;
	}
}
