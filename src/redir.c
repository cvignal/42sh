/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 11:36:21 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/19 12:41:49 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"

static void	add_to_redir_list(t_command *command, t_redir *redir)
{
	t_redir	*iter;

	iter = command->redir_list;
	if (!iter)
		command->redir_list = redir;
	else
	{
		while (iter->next)
			iter = iter->next;
		iter->next = redir;
	}
}

int		add_redir(t_command *command, t_ttype type, char *arg, t_redir_act act)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(*new_redir));
	if (!new_redir)
		return (1);
	new_redir->target = ft_strdup(arg);
	if (!new_redir->target)
	{
		free(new_redir);
		return (1);
	}
	new_redir->type = type;
	new_redir->next = NULL;
	new_redir->redir_act = act;
	add_to_redir_list(command, new_redir);
	return (0);
}
