/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 01:21:02 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/09 01:33:22 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"

static t_var	*alloc_var(const char *name, const char *value)
{
	t_var	*var;

	var = malloc(sizeof(*var));
	if (!var)
		return (NULL);
	if (!(var->name = ft_strdup(name)))
	{
		free(var);
		return (NULL);
	}
	if (!(var->value = ft_strdup(value)))
	{
		free(var->value);
		free(var);
		return (NULL);
	}
	var->left = NULL;
	var->right = NULL;
	return (var);
}

static t_var	**find_var_position(t_var **current, const char *name)
{
	int			ret;

	if (!*current)
		return (current);
	ret = ft_strcmp((*current)->name, name);
	if (!ret)
		return (current);
	if (ret < 0)
		return (find_var_position(&(*current)->left, name));
	else
		return (find_var_position(&(*current)->right, name));
}

int				add_shell_var(t_shell *shell, const char *name,
		const char *value)
{
	t_var	**position;

	position = find_var_position(&shell->vars, name);
	if (!*position)
	{
		if (!(*position = alloc_var(name, value)))
			return (1);
	}
	else
	{
		if ((*position)->value)
			free((*position)->value);
		if (!((*position)->value = ft_strdup(value)))
			return (1);
	}
	return (0);
}

t_var			*get_var(t_var *vars, const char *name)
{
	int			ret;

	if (vars)
	{
		ret = ft_strcmp(vars->name, name);
		if (!ret)
			return (vars);
		else if (ret < 0)
			return (get_var(vars->left, name));
		else
			return (get_var(vars->right, name));
	}
	return (NULL);
}
