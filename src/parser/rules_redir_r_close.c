/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir_r_close.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 19:38:21 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/11 22:49:22 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "shell.h"

static t_redir	*create_redir_close(char *data)
{
	t_redir		*new_redir;

	new_redir = malloc(sizeof(*new_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = TT_REDIR_R_CLOSE;
	new_redir->next = NULL;
	new_redir->redir_act = &redir_r_close;
	new_redir->target = NULL;
	new_redir->applied = 0;
	if (ft_isdigit(*data))
	{
		new_redir->in = ft_atoi(data);
		if (new_redir->in < 0 || new_redir->in > 9)
		{
			free(new_redir);
			return (NULL);
		}
	}
	else
		new_redir->in = 1;
	return (new_redir);
}

int				rule_redir_r_close(t_parser *parser, t_ast_token *list)
{
	t_ast		*instr;
	t_redir		*redir;
	t_redir		*iter;

	if (!(redir = create_redir_close(list->data)))
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
	return (0);
}
