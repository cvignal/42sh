/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 09:04:48 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/11 03:45:21 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"

t_var			*copy_env(const char **env)
{
	t_var	*res;
	int		i;

	res = NULL;
	i = 0;
	while (env[i])
	{
		if (set_var_full(&res, env[i], 1))
		{
			free_vars(&res);
			return (NULL);
		}
		++i;
	}
	return (res);
}

t_var			*copy_vars(t_var *vars, int only_exported)
{
	t_var	*copy;

	copy = NULL;
	while (vars)
	{
		if ((only_exported && vars->exported) || !only_exported)
		{
			if (set_var_full(&copy, vars->var, vars->exported))
			{
				free_vars(&copy);
				return (NULL);
			}
		}
		vars = vars->next;
	}
	return (copy);
}

void				free_vars(t_var **vars)
{
	t_var			*next;
	t_var			*iter;

	iter = *vars;
	while (iter)
	{
		next = iter->next;
		free(iter);
		iter = next;
	}
	*vars = NULL;
}
