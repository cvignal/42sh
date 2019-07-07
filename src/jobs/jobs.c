/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:52:57 by agrouard          #+#    #+#             */
/*   Updated: 2019/07/06 12:35:59 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"
#include "fill_line.h"

#include <unistd.h>

t_job		*new_job(void)
{
	t_job *job;

	if (!(job = ft_memalloc(sizeof(t_job))))
		return (NULL);
	job->notified = 1;
	return (job);
}

static void	add_to_shell(t_shell *shell, t_job *job)
{
	t_job	*j;

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
}

int			register_job(t_shell *shell, t_job *job)
{
	if (!job->proc)
	{
		free_job(shell, job);
		return (0);
	}
	add_to_shell(shell, job);
	if (!job->async)
		return (job_fg(shell, job, 0));
	if (!check_validity(shell))
		report_job(shell, job, 1 | 2, STDERR_FILENO);
	set_bg_pid(shell, job->last->pid);
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
	ast->job->last = *p;
	if (!ast->job->pgid)
		ast->job->pgid = ast->pid;
	if (ast->pid)
		setpgid(ast->pid, ast->job->pgid);
	(*p)->ret = ast->ret;
	(*p)->pid = ast->pid;
	(*p)->name = ast_to_string(ast);
	return (0);
}
