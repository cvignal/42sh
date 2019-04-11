/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 11:41:34 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/11 02:35:23 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	exit_error(const char *msg)
{
	ft_dprintf(2, "%s: env: %s\n", EXEC_NAME, msg);
	return (-1);
}

static int	option_u(char **args, int *i, t_var **vars)
{
	if (!ft_strcmp(args[*i], "-u"))
	{
		++(*i);
		if (!args[*i])
			return (exit_error("option requires an argument -- u"));
		remove_var(vars, args[*i], REMOVE_VAR_ENV | REMOVE_VAR_LOCAL);
	}
	return (0);
}

static int	option_capp(char **args, int *i, t_var **vars)
{
	if (!ft_strcmp(args[*i], "-P"))
	{
		++(*i);
		if (!args[*i])
			return (exit_error("option requires an argument -- P"));
		return (set_var(vars, "PATH", args[*i], 1));
	}
	return (0);
}

int			builtin_env_get_opts(char **args, t_var **env)
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
				free_vars(env);
			++j;
		}
		if (option_u(args, &i, env))
			return (1);
		if (option_capp(args, &i, env))
			return (1);
		++i;
	}
	return (i);
}
