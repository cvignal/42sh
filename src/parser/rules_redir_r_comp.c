/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir_r_comp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 12:43:13 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/11 22:27:54 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "shell.h"
#include "libft.h"

static t_redir	*create_redir_comp(char *data)
{
	t_redir		*new_redir;

	new_redir = create_redir(TT_REDIR_R_COMP, NULL, &redir_r_comp);
	if (!new_redir)
		return (NULL);
	new_redir->in = 1;
	if (ft_isdigit(*data))
	{
		new_redir->in = ft_atoi(data);
		if (new_redir->in < 0 || new_redir->in > 9)
		{
			free(new_redir);
			return (NULL);
		}
		while (ft_isdigit(*data))
			++data;
	}
	new_redir->out = ft_atoi(data + 2);
	if (new_redir->out < 0 || new_redir->out > 9)
	{
		free(new_redir);
		return (NULL);
	}
	return (new_redir);
}

int				rule_redir_r_comp(t_parser *parser, t_ast_token *list)
{
	t_ast		*instr;
	t_redir		*redir;
	t_redir		*iter;

	redir = create_redir_comp(list->next->data);
	instr = parser->pss->ret;
	iter = instr->redir_list;
	if (!iter)
		instr->redir_list = redir;
	else
	{
		while (iter->next)
			iter = iter->next;
		iter->next = redir;
	}
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	return (0);
}
