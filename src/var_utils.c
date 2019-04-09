/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 08:16:59 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/09 09:14:14 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"

void	concat_var(t_var *var, const char *name, const char *value)
{
	int		i;

	i = 0;
	while (name[i])
	{
		var->var[i] = name[i];
		++i;
	}
	var->len_name = i;
	dst[i++] = '=';
	i = 0;
	while (value[i])
	{
		var->var[var->len_name + i + 1] = value[i];
		++i;
	}
	var->var[size_name + i] = 0;
	var->len_value = i;
}

int		check_var(const char *name, const char *value)
{
	size_t	size_name;
	size_t	size_value;

	if ((size_name = ft_strlen(name)) > VAR_MAX)
	{
		ft_dprintf(STDERR_FILENO, "%s: variable name too long\n", EXEC_NAME);
		return (1);
	}
	else if ((size_value = ft_strlen(value)) > VAR_MAX)
	{
		ft_dprintf(STDERR_FILENO, "%s: variable content too long\n", EXEC_NAME);
		return (1);
	}
	return (0);
}

t_var	*create_var(const char *value, int exported)
{
	t_var	*var;
	size_t	len_value;

	len_value = ft_strlen(value);
	if (len_value > VAR_MAX * 2 + 2)
	{
		ft_dprintf(STDERR_FILENO, "%s: variable too long\n", EXEC_NAME);
		return (NULL);
	}
	if (!(var = malloc(sizeof(*var))))
	{
		ft_dprintf(STDERR_FILENO, "%s: unable to allocate memory\n", EXEC_NAME);
		return (NULL);
	}
	var->len_name = ft_strchr(value, "=") - value - 1;
	var->len_value = len_value - var->len_name - 1;
	var->exported = exported;
	return (var);
}

t_var	*alloc_var(const char *name, const char *value, int exported)
{
	t_var	*var;

	if (check_var(name, value))
		return (NULL);
	else if (!(var = malloc(sizeof(*var))))
	{
		ft_dprintf(STDERR_FILENO, "%s: unable to allocate memory\n", EXEC_NAME);
		return (NULL);
	}
	concat_var(var, name, value);
	var->exported = exported;
	return (var);
}

char	**build_env(t_shell *shell)
{
	char	**env;
	size_t	size_env;
	t_var	*iter;
	int		i;

	size_env = 0;
	iter = shell->env_vars;
	while (iter)
	{
		if (iter->exported)
			++size_env;
		iter = iter->next;
	}
	if (!(env = malloc(sizeof(*env) * (size_env + 1))))
	{
		ft_dprintf(STDERR_FILENO, "%s: unable to allocate memory\n", EXEC_NAME);
		return (NULL);
	}
	iter = shell->env_vars;
	i = 0;
	while (iter)
	{
		if (iter->exported)
			env[i++] = iter->var;
		iter = iter->next;
	}
	env[i] = NULL;
	return (env);
}
