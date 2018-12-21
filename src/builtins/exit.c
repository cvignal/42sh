/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 08:45:36 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/21 14:46:35 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"

int	builtin_exit(t_shell *shell, char **args)
{
	size_t	arg_count;

	(void)shell;
	arg_count = 0;
	while (args[arg_count])
		++arg_count;
	if (arg_count > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	remove_env(shell);
	free_shell(shell);
	exit(arg_count == 2 ? ft_atoi(args[1]) : 0);
}
