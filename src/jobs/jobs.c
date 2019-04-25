/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:52:57 by agrouard          #+#    #+#             */
/*   Updated: 2018/12/12 09:54:33 by agrouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"

#include <unistd.h>
#include <signal.h>

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

static void	print_job_infos(t_shell *shell, t_job *job, int opts)
{
	ft_printf("[%d]", job->index);
	if (job == shell->curr)
		ft_putchar('+');
	else if (job == shell->prev)
		ft_putchar('-');
	else
		ft_putchar(' ');
	ft_putstr("  ");
	if (opts == 'l')
		ft_printf("%d ", job->pgid);
}

static void	print_job_state(t_job *job)
{
	static char	*status[] = {"None", "Running", "Stopped", "Done"};

	ft_putstr(status[job->state]);
	if (job->state == JOB_DONE && job->last->ret)
		ft_printf("(%d)", job->last->ret);
	if (job->state == JOB_STOPPED)
	{
		if (job->last->ret - 128 == SIGSTOP)
			ft_putstr("(SIGSTOP)");
		if (job->last->ret - 128 == SIGTTIN)
			ft_putstr("(SIGTTIN)");
		if (job->last->ret - 128 == SIGTTOU)
			ft_putstr("(SIGTTOU)");
	}
}

t_job		*report_job(t_shell *shell, t_job *job, int opts)
{
	t_job		*next;

	next = job->next;
	if (opts == 'p')
		ft_printf("%d\n", job->pgid);
	else
	{
		print_job_infos(shell, job, opts);
		print_job_state(job);
		ft_putstr("\t\t");
		print_job_command(job);
		if (job->state == JOB_DONE)
			free_job(shell, job);
	}
	return (next);
}
