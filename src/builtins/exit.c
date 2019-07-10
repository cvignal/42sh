/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 08:45:36 by gchainet          #+#    #+#             */
/*   Updated: 2019/07/09 17:27:39 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>

#include "shell.h"
#include "jobs.h"
#include "fill_line.h"
#include "libft.h"

static int	exit_value(t_shell *shell, char *args)
{
	int		ret;
	char	*a;

	reset_terminal_mode(shell);
	if (!args)
		ret = ft_atoi(get_var_value(get_var(shell->vars, SPECIAL_PARAM_QMARK)));
	else
	{
		a = args;
		if (*args == '-' || *args == '+')
			a = args + 1;
		if ((ret = parse_number(a)) == -1 || *a == 0)
		{
			ret = 2;
			ft_dprintf(2, "%s: exit: %s: numeric argument required\n"
					, EXEC_NAME, args);
		}
		else
			ret = ft_atoi(args);
	}
	free_shell(shell);
	exit(ret);
}

static int	verif_children(t_shell *shell)
{
	t_job *job;

	if (shell->last_cmd != builtin_exit)
	{
		job = shell->jobs;
		while (job)
		{
			if (job->state == JOB_STOPPED)
			{
				ft_dprintf(2, "There are stopped jobs.\n");
				return (1);
			}
			job = job->next;
		}
	}
	return (0);
}

int			builtin_exit(t_shell *shell, char **args)
{
	size_t	arg_count;

	if (!check_validity(shell) && verif_children(shell))
		return (1);
	arg_count = 0;
	while (args && args[arg_count])
		++arg_count;
	if (arg_count > 2)
	{
		ft_dprintf(2, "%s: exit: too many arguments\n", EXEC_NAME);
		return (1);
	}
	add_to_history(shell->line.data, shell, 0);
	if (close(shell->fd_op) == -1)
		ft_dprintf(2, "Error on closing the tty fd\n");
	return (exit_value(shell, args ? args[1] : NULL));
}
