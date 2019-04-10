/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 08:16:59 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 09:01:02 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"

static char	**alloc_env(t_var *vars)
{
	char	**env;
	size_t	size_env;

	size_env = 0;
	while (vars)
	{
		if (vars->exported)
			++size_env;
		vars = vars->next;
	}
	if (!(env = malloc(sizeof(*env) * (size_env + 1))))
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
	return (env);
}

void		concat_var(t_var *var, const char *name, const char *value)
{
	int		i;

	i = 0;
	while (name[i])
	{
		var->var[i] = name[i];
		++i;
	}
	var->len_name = i;
	var->var[i] = '=';
	i = 0;
	while (value[i])
	{
		var->var[var->len_name + i + 1] = value[i];
		++i;
	}
	var->var[var->len_name + i + 1] = 0;
	var->len_value = i;
}

int			check_var(const char *name, const char *value)
{
	if (ft_strlen(name) > VAR_MAX || ft_strlen(value) > VAR_MAX)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, ERR_LEN_VAR);
		return (1);
	}
	return (0);
}

char		**build_env(t_var *vars)
{
	char	**env;
	int		i;

	if (!(env = alloc_env(vars)))
		return (NULL);
	i = 0;
	while (vars)
	{
		if (vars->exported)
			env[i++] = vars->var;
		vars = vars->next;
	}
	env[i] = NULL;
	return (env);
}
