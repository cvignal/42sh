/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 08:14:44 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/15 19:38:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	exit_error(const char *msg)
{
	ft_dprintf(2, "%s: setenv: %s\n", EXEC_NAME, msg);
	return (1);
}

static int	print_env(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->env[i])
		ft_dprintf(shell->fd_op, "%s\n", shell->env[i++]);
	return (0);
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
	{
		if (ft_strlen(args[1]) > VAR_MAX || ft_strlen(args[2]) > VAR_MAX)
		{
			ft_dprintf(2, "%s: variable too long\n", EXEC_NAME);
			return (1);
		}
		if (set_env_var(shell, args[1], args[2]))
			return (1);
		if (!ft_strcmp(args[1], "PATH"))
			sanitize_hash(shell);
		return (0);
	}
	if (arg_count == 1)
		return (print_env(shell));
	return (exit_error("usage: setenv var value"));
}
