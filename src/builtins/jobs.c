/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:21:25 by agrouard          #+#    #+#             */
/*   Updated: 2018/12/12 09:28:44 by agrouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"

#include <unistd.h>

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

int		parse_opts(int *i, char **argv)
{
	char	*str;
	int		opts;

	opts = 0;
	*i = 1;
	while (argv[*i] && argv[*i][0] == '-' && argv[*i][1])
	{
		if (ft_strequ(argv[(*i)++], "--"))
			break ;
		str = argv[(*i) - 1] + 1;
		while (*str)
		{
			if (*str != 'l' && *str != 'p')
				return (fail("jobs", "usage", "jobs [-lp] [jobspec ...]", -1));
			opts = *str;
			str++;
		}
	}
	return (opts);
}

int		builtin_jobs(t_shell *shell, char **argv)
{
	t_job	*j;
	int		i;
	int		opts;
	int		ret;

	ret = 0;
	update_jobs(shell);
	if ((opts = parse_opts(&i, argv)) == -1)
		return (1);
	if (!argv[i])
	{
		j = shell->jobs;
		while (j)
			j = report_job(shell, j, opts);
	}
	while (argv[i])
	{
		j = parse_jobspec(shell, argv[i++]);
		if (j)
			report_job(shell, j, opts);
		else
			ret = fail("jobs", argv[i - 1], "no such job", 1);
	}
	return (ret);
}

int		builtin_fg(t_shell *shell, char **argv)
{
	t_job	*target;

	update_jobs(shell);
	target = NULL;
	if (argv[1] == NULL)
	{
		if (!(target = shell->curr))
			return (fail("fg", "current", "no such job", 1));
	}
	else
	{
		if (!(target = parse_jobspec(shell, argv[1])))
			return (fail("fg", argv[1], "no such job", 1));
	}
	if (job_is_done(target))
		return (fail("fg", NULL, "job has terminated", 1));
	print_job_command(target);
	job_fg(shell, target, 1);
	return (0);
}

int		builtin_bg(t_shell *shell, char **argv)
{
	t_job	*target;

	update_jobs(shell);
	target = NULL;
	if (argv[1] == NULL)
	{
		if (!(target = shell->curr))
			return (fail("bg", "current", "no such job", 1));
	}
	else
	{
		if (!(target = parse_jobspec(shell, argv[1])))
			return (fail("bg", argv[1], "no such job", 1));
	}
	if (job_is_done(target))
		return (fail("bg", NULL, "job has terminated", 1));
	ft_printf("[%d] ", target->index);
	print_job_command(target);
	job_bg(target, 1);
	return (0);
}
