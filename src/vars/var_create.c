/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:02:04 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/02 01:47:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"

static int		separate_name_value(const char *full, char *name,
		const char **value)
{
	int		pos;

	pos = 0;
	while (full[pos] && full[pos] != '=')
	{
		if (pos > VAR_MAX)
			return (1);
		name[pos] = full[pos];
		++pos;
	}
	name[pos] = 0;
	if (full[pos] != '=')
		return (1);
	*value = full + pos + 1;
	return (0);
}

t_var			*alloc_var(const char *name, const char *value, int exported)
{
	t_var	*var;

	if (!(var = malloc(sizeof(*var))))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		return (NULL);
	}
	ft_bzero(var, sizeof(*var));
	if (concat_var(var, name, value))
	{
		free(var);
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		return (NULL);
	}
	var->exported = exported;
	var->next = NULL;
	return (var);
}

void			add_to_vars(t_var **to, t_var *from)
{
	t_var	*iter;

	if (!*to)
		*to = from;
	else
	{
		iter = *to;
		while (iter->next)
			iter = iter->next;
		iter->next = from;
	}
}

int				set_var(t_var **vars, const char *name, const char *value,
		int exported)
{
	t_var		*var;

	if (check_var(name))
		return (1);
	if (!(var = get_var(*vars, name)))
	{
		if (!(var = alloc_var(name, value, exported)))
			return (1);
		add_to_vars(vars, var);
	}
	else
		concat_var(var, name, value);
	var->exported = exported;
	return (0);
}

int				set_var_full(t_var **vars, const char *value, int exported)
{
	char		var_name[VAR_MAX + 1];
	const char	*var_value;

	if (separate_name_value(value, var_name, &var_value))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, ERR_LEN_VAR);
		return (1);
	}
	return (set_var(vars, var_name, var_value, exported));
}
