/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 06:58:54 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/09 08:54:45 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"

static void	remove_var_first(t_var **var)
{
	t_var	*tmp;

	tmp = (*var)->next;
	free(*var);
	*var = tmp;
}

static void	remove_var_middle(t_var *vars, const char *name)
{
	t_var	*prev;

	prev = NULL;
	while (vars)
	{
		if (!ft_strncmp(vars->var, name, size_name) && vars->var[size_name] == '=')
		{
			if (prev)
				prev->next = vars->next;
			free(vars);
			return ;
		}
		prev = vars;
		vars = vars->next;
	}
}

int				set_var(t_shell *shell, const char *name, const char *value,
		int exported)
{
	t_var		*var;
	int			new_var;

	if (check_var(name, value))
		return (1);
	new_var = 0;
	if (!(var = get_var(shell, name)))
	{
		if (!(var = alloc_var(name, value, exported)))
			return (1);
		new_var = 1;
		var->next = shell->vars;
		shell->vars = var;
	}
	concat_var(var, name, value);
	return (0);
}

t_var			*get_var(t_shell *shell, const char *name)
{
	t_var		*iter;
	size_t		len_name;

	len_name = ft_strlen(name);
	iter = shell->vars;
	while (iter)
	{
		if (!ft_strncmp(iter->var, name, len_name) && iter->var[len_name] == '=')
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

void		remove_var(t_shell *shell, const char *name)
{
	size_t	size_name;

	size_name = ft_strlen(name);
	if (shell->vars && !ft_strncmp(shell->vars->var, name, size_name)
			&& shell->vars->var[size_name] == '=')
		remove_var_first(&shell->env_vars);
	else
		remove_var_middle(shell->vars, name);
}
