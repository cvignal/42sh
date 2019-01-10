/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 08:14:44 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 19:03:28 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	exit_error(const char *msg)
{
	ft_dprintf(2, "%s: setenv: %s\n", EXEC_NAME, msg);
	return (1);
}

static void	print_env(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->env[i])
		ft_printf("%s\n", shell->env[i++]);
}

int			builtin_setenv(t_shell *shell, char **args)
{
	size_t	arg_count;

	arg_count = 0;
	while (args[arg_count])
		++arg_count;
	if (arg_count > 3)
		return (exit_error("too many arguments"));
	else if (arg_count == 3)
		return (set_env_var(shell, args[1], args[2]));
	if (arg_count == 1)
	{
		print_env(shell);
		return (0);
	}
	return (exit_error("usage: setenv var value"));
}
