/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:52:57 by agrouard          #+#    #+#             */
/*   Updated: 2018/12/12 09:55:10 by agrouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "jobs.h"
#include "shell.h"

int			register_job(t_shell *shell, t_job *job, int foreground)
{
	t_job	*j;

	if (!job->proc)
	{
		free_job(shell, job);
		return (0);
	}
	if (!(j = shell->jobs))
	{
		shell->jobs = job;
		job->index = 1;
	}
	else
	{
		while (j->next)
			j = j->next;
		j->next = job;
		job->index = j->index + 1;
	}
	if (foreground)
		return (job_fg(shell, job, 0));
	job_bg(job, 0);
	return (0);
}

int			register_proc(t_ast *ast)
{
	t_proc	**p;

	p = &ast->job->proc;
	if (ast->job->last)
		p = &(ast->job->last)->next;
	if (!(*p = ft_memalloc(sizeof(t_proc))))
		return (1);
	(*p)->pid = ast->pid;
	(*p)->command = ft_strdup("TODO");
	ast->job->last = *p;
	if (!ast->job->pgid)
		ast->job->pgid = ast->pid;
	setpgid(ast->pid, ast->job->pgid);
	return (0);
}

t_job	*new_job(void)
{
	t_job	*j;

	if (!(j = malloc(sizeof(t_job))))
		return (NULL);
	j->proc = NULL;
	j->last = NULL;
	j->pgid = 0;
	j->index = 0;
	j->state = JOB_NONE;
	j->next = NULL;
	return (j);
}

void	free_job(t_shell *shell, t_job *job)
{
	t_proc	*tmp;
	t_job	*j;

	if ((j = shell->jobs) == job)
		shell->jobs = job->next;
	else if (j)
	{
		while (j->next)
		{
			if (j->next == job)
			{
				j->next = job->next;
				break ;
			}
			j = j->next;
		}
	}
	while (job->proc)
	{
		tmp = job->proc->next;
		free(job->proc->command);
		free(job->proc);
		job->proc = tmp;
	}
	free(job);
}

t_job	*find_job(t_shell *shell, int index)
{
	t_job	*j;

	j = shell->jobs;
	while (j)
	{
		if (j->index == index)
			return (j);
		j = j->next;
	}
	return (NULL);
}
