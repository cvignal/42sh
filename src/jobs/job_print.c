/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_print.c                                        :+:      :+:    :+:   */
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

static void		print_job_infos(t_shell *shell, t_job *job)
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

static void	print_job_state(t_job *job)
{
	static char	*status[] = {"None", "Running", "Stopped", "Done"};

	ft_printf(" %s", status[job->state]);
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

static void print_pipeline(t_job *job)
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
	}
	ft_putchar('\n');
	return (next);
}
