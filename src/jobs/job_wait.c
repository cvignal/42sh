/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:52:57 by agrouard          #+#    #+#             */
/*   Updated: 2019/07/06 16:56:22 by agrouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"
#include <sys/wait.h>
#include <unistd.h>

static t_proc	*find_proc(t_shell *shell, pid_t pid, t_job **job)
{
	t_job	*j;
	t_proc	*p;

	j = shell->jobs;
	while (j)
	{
		if (job)
			*job = j;
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

static void		update_proc(t_shell *shell, pid_t pid, int status)
{
	t_job	*j;
	t_proc	*p;

	if (!(p = find_proc(shell, pid, &j)))
		return ;
	j->notified = 0;
	p->status = status;
	if (WIFEXITED(status))
	{
		p->done = 1;
		p->ret = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
	{
		p->done = 1;
		p->ret = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			shell->ctrlc = 1;
	}
	else if (WIFSTOPPED(status))
	{
		j->state = JOB_STOPPED;
		p->stopped = 1;
		p->ret = 128 + WSTOPSIG(status);
	}
}

int				wait_job(t_shell *shell, t_job *job)
{
	pid_t	pid;
	int		status;
	int		options;

	options = WNOHANG | (shell->is_subshell ? 0 : WUNTRACED);
	while (!job_is_stopped(job))
	{
		if ((pid = waitpid(-1, &status, options)) <= 0)
			continue;
		update_proc(shell, pid, status);
	}
	while ((pid = waitpid(-1, &status, WUNTRACED | WNOHANG)) > 0)
		update_proc(shell, pid, status);
	status = job->async ? 0 : job->last->ret;
	if (job_is_done(job))
	{
		if (WIFSIGNALED(job->last->status))
			report_job(shell, job, 4, STDERR_FILENO);
		free_job(shell, job);
	}
	return (status);
}

void			job_notify(t_shell *shell)
{
	t_job *job;

	job = shell->jobs;
	while (job)
	{
		if (!job->notified)
			job = report_job(shell, job, 1 | 4 | 8, STDERR_FILENO);
		else
			job = job->next;
	}
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
