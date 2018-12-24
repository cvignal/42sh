/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 11:36:21 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/24 07:40:21 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "21sh.h"
#include "libft.h"

void		add_to_redir_list(t_command *command, t_redir *redir)
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

t_redir		*create_redir(t_ttype type, char *arg, t_redir_act act)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(*new_redir));
	if (!new_redir)
		return (NULL);
	new_redir->target = ft_strdup(arg);
	if (!new_redir->target)
	{
		free(new_redir);
		return (NULL);
	}
	new_redir->type = type;
	new_redir->next = NULL;
	new_redir->redir_act = act;
	return (new_redir);
}
