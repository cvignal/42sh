/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 08:22:56 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/11 02:33:59 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	exit_error(const char *msg)
{
	ft_dprintf(2, "%s: unsetenv: %s\n", EXEC_NAME, msg);
	return (1);
}

int			builtin_unsetenv(t_shell *shell, char **args)
{
	size_t	arg_count;

	arg_count = 0;
	while (args[arg_count])
		++arg_count;
	if (arg_count > 2)
		return (exit_error("too many arguments"));
	else if (arg_count < 2)
		return (exit_error("usage: unsetenv var"));
	remove_var(&shell->vars, args[1], REMOVE_VAR_ENV);
	if (!ft_strcmp(args[1], "PATH"))
		sanitize_hash(shell);
	return (0);
}
