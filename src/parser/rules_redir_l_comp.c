/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir_l_comp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 11:05:09 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 11:37:37 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "shell.h"
#include "libft.h"

static t_redir	*create_redir_l_comp(char *data)
{
	t_redir		*new_redir;

	if (!(new_redir = create_redir(TT_REDIR_L_COMP, NULL, &redir_l_comp)))
		return (NULL);
	new_redir->in = 0;
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
	if (!*(data + 2))
		new_redir->out = -1;
	return (new_redir);
}

int				rule_redir_l_comp(t_parser *parser, t_token *list)
{
	t_ast		*instr;
	t_redir		*redir;
	t_redir		*iter;
	t_token		*next;

	(void)list;
	if (!(redir = create_redir_l_comp(parser->input_queue->data)))
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
