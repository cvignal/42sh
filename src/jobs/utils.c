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
		free(job->proc->name);
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

int		parse_number(char *str)
{
	unsigned	res;

	res = 0;
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str++ - '0');
		if ((long)(int)res != (long)res)
			return (-1);
	}
	if (*str != '\0')
		return (-1);
	return (res);
}

t_job	*parse_jobspec(t_shell *shell, char *jobspec)
{
	int	num;

	if (jobspec[0] != '%')
		return (0);
	if ((num = parse_number(jobspec + 1)) != -1)
		return (find_job(shell, num));
	if (jobspec[1] == '%' || jobspec[1] == '+')
		return (shell->curr);
	if (jobspec[1] == '-')
		return (shell->prev);
	return (NULL);
}
