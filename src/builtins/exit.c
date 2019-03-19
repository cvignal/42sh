/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 08:45:36 by gchainet          #+#    #+#             */
/*   Updated: 2019/03/19 16:49:47 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include "shell.h"
#include "fill_line.h"
#include "libft.h"

static int	exit_value(t_shell *shell, char **args)
{
	int		ret;

	if (args[1] && !ft_isdigit(args[1][0]) && args[1][0] != '-'
			&& args[1][0] != '+')
	{
		free_shell(shell);
		exit(255);
	}
	if (args[1])
	{
		ret = ft_atoi(args[1]);
		free_shell(shell);
		exit(ret);
	}
	else
	{
		free_shell(shell);
		exit(0);
	}
}

int			builtin_exit(t_shell *shell, char **args)
{
	size_t	arg_count;

	arg_count = 0;
	while (args[arg_count])
		++arg_count;
	if (arg_count > 2)
	{
		ft_dprintf(2, "%s: exit: too many arguments\n", EXEC_NAME);
		return (1);
	}
	add_to_history(shell->line.data, shell, 0);
	if (close(shell->fd_op) == -1)
		ft_dprintf(2, "Error on closing the tty fd\n");
	remove_env(shell);
	return (exit_value(shell, args));
}
