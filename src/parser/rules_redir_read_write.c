/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir_read_write.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 01:02:14 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/12 02:24:34 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static t_redir	*create_redir_rw(t_ast_token *list)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(*new_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = TT_REDIR_RW;
	new_redir->next = NULL;
	new_redir->redir_act = &redir_rw;
	new_redir->target = list->next->data;
	new_redir->applied = 0;
	if (ft_isdigit(*(char *)list->data))
	{
		new_redir->in = ft_atoi(list->data);
		if (new_redir->in < 0 || new_redir->in > 9)
		{
			free(new_redir);
			return (NULL);
		}
	}
	else
		new_redir->in = 0;
	return (new_redir);
}

int				rule_redir_rw(t_parser *parser, t_ast_token *list)
{
	t_ast		*instr;
	t_redir		*redir;
	t_redir		*iter;

	if (!(redir = create_redir_rw(list)))
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
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	free(pop_ast_token(&parser->input_queue));
	return (0);
}
