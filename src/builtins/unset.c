/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:50:43 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/11 03:50:30 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	exit_error(const char *msg)
{
	ft_dprintf(2, "%s: unset: %s\n", EXEC_NAME, msg);
	return (1);
}

static int	handle_options(const char *arg, int *options)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'f' || arg[i] == 'v' || arg[i] == 'n')
			*options |= (1 << (arg[i] - 'a'));
		else
			return (1);
		++i;
	}
	return (0);
}

static int	builtin_unset_internal(t_shell *shell, char **args, int i,
		int options)
{
	(void)options;
	while (args[i])
	{
		remove_var(&shell->vars, args[i], REMOVE_VAR_ENV | REMOVE_VAR_LOCAL);
		if (!ft_strcmp(args[1], "PATH"))
			sanitize_hash(shell);
		++i;
	}
	return (0);
}

int			builtin_unset(t_shell *shell, char **args)
{
	size_t	i;
	int		options;
	int		options_over;

	i = 1;
	options = 0;
	options_over = 0;
	while (args[i])
	{
		if (!options_over)
		{
			if (args[i][0] == '-')
			{
				if (handle_options(args[i], &options))
					return (exit_error(ERR_BUILTIN_UNSET_ARG));
			}
			else
				options_over = 1;
		}
		if (options_over)
			return (builtin_unset_internal(shell, args, i, options));
		++i;
	}
	return (0);
}
