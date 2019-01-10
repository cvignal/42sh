/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 11:41:34 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 19:03:13 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	exit_error(const char *msg)
{
	ft_dprintf(2, "%s: env: %s\n", EXEC_NAME, msg);
	return (-1);
}

static int	option_u(char **args, int *i, t_shell *tmp_shell)
{
	if (!ft_strcmp(args[*i], "-u"))
	{
		++(*i);
		if (!args[*i])
			return (exit_error("option requires an argument -- u"));
		remove_env_value(tmp_shell, args[*i]);
	}
	return (0);
}

static int	option_capp(char **args, int *i, t_shell *tmp_shell)
{
	if (!ft_strcmp(args[*i], "-P"))
	{
		++(*i);
		if (!args[*i])
			return (exit_error("option requires an argument -- P"));
		set_env_var(tmp_shell, "PATH", args[*i]);
	}
	return (0);
}

int			builtin_env_get_opts(char **args, t_shell *tmp_shell)
{
	int		i;
	int		j;

	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j])
		{
			if (args[i][j] == 'i')
				remove_env(tmp_shell);
			++j;
		}
		if (option_u(args, &i, tmp_shell))
			return (1);
		if (option_capp(args, &i, tmp_shell))
			return (1);
		++i;
	}
	return (i);
}
