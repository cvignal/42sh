/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:02:04 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 04:21:44 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"

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
	ft_strcpy(var->var, value);
	var->len_name = ft_strchr(value, '=') - value - 1;
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

int				set_var(t_var **vars, const char *name, const char *value,
		int exported)
{
	t_var		*var;

	if (check_var(name, value))
		return (1);
	if (!(var = get_var(*vars, name)))
	{
		if (!(var = alloc_var(name, value, exported)))
			return (1);
		var->next = *vars;
		*vars = var;
	}
	concat_var(var, name, value);
	return (0);
}

static int		separate_name_value(const char *full, char *name, char *value)
{
	int		pos;
	int		shift;

	pos = 0;
	while (full[pos] && full[pos] != '=')
	{
		if (pos > VAR_MAX)
			return (1);
		name[pos] = full[pos];
		++pos;
	}
	name[pos] = 0;
	shift = pos;
	if (full[pos] != '=')
		return (1);
	++pos;
	while (full[pos])
	{
		if (pos - shift - 1 > VAR_MAX)
			return (1);
		value[pos - shift - 1] = full[pos];
		++pos;
	}
	value[pos - shift - 1] = 0;
	return (0);
}

int				set_var_full(t_var **vars, const char *value, int exported)
{
	t_var		*var;
	char		var_name[VAR_MAX + 1];
	char		var_value[VAR_MAX + 1];

	if (separate_name_value(value, var_name, var_value))
	{
		ft_dprintf(STDERR_FILENO, "%:: invalid variable\n", EXEC_NAME);
		return (1);
	}
	if (!(var = get_var(*vars, var_name)))
	{
		if (!(var = alloc_var(var_name, var_value, exported)))
			return (1);
		var->next = *vars;
		*vars = var;
	}
	else
		concat_var(var, var_name, var_value);
	return (0);
}

