/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir_comp_generic.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 11:06:52 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 11:15:52 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_redir	*create_redir_comp(char *data, t_ttype type, t_redir_act act)
{
	t_redir		*new_redir;

	new_redir = create_redir(type, NULL, act);
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


int				create_redir_comp_generic(t_parser *parser, t_ttype type,
		t_redir_act act)
{
	t_ast		*instr;
	t_redir		*redir;
	t_redir		*iter;
	t_token		*next;

	if (!(redir = create_redir_comp(parser->input_queue->data, type, act)))
		return (1);
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
	next = parser->input_queue->next;
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	parser->input_queue = next;
	return (0);
}
