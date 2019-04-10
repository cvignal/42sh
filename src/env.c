/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 09:04:48 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 07:19:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"

t_var			*copy_env(const char **env)
{
	t_var	*res;
	t_var	*var;
	int		i;

	res = NULL;
	i = 0;
	while (env[i])
	{
		if (!(var = create_var(env[i], 1)))
		{
			while (res)
			{
				free(res);
				res = res->next;
			}
			return (NULL);
		}
		var->next = res;
		res = var;
		++i;
	}
	return (var);
}

static t_var	*copy_var(t_var *var)
{
	t_var	*copy;

	copy = malloc(sizeof(*copy));
	if (!copy)
		return (NULL);
	ft_strcpy(copy->var, var->var);
	copy->exported = var->exported;
	copy->next = NULL;
	return (copy);
}

t_var			*copy_env_from_vars(t_var *vars)
{
	t_var	*res;
	t_var	*current;

	res = NULL;
	while (vars)
	{
		if (vars->exported)
		{
			if (!(current = copy_var(vars)))
			{
				ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME,
						MEMORY_ERROR_MSG);
				free_vars(&res);
				return (NULL);
			}
			current->next = res;
			res = current;
		}
		vars = vars->next;
	}
	return (res);
}

void			free_vars(t_var **vars)
{
	t_var	*i;
	t_var	*next;

	i = *vars;
	while (i)
	{
		next = i->next;
		free(i);
		i = next;
	}
	*vars = NULL;
}
