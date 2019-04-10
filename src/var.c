/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 06:58:54 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 04:15:13 by gchainet         ###   ########.fr       */
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

static void	remove_var_middle(t_var *vars, const char *name, size_t size_name)
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

t_var			*get_var(t_var *vars, const char *name)
{
	size_t		len_name;

	len_name = ft_strlen(name);
	while (vars)
	{
		if (!ft_strncmp(vars->var, name, len_name) && vars->var[len_name] == '=')
			return (vars);
		vars = vars->next;
	}
	return (NULL);
}

void		remove_var(t_var **vars, const char *name)
{
	size_t	size_name;

	size_name = ft_strlen(name);
	if (*vars && !ft_strncmp((*vars)->var, name, size_name)
			&& (*vars)->var[size_name] == '=')
		remove_var_first(vars);
	else
		remove_var_middle(*vars, name, size_name);
}
