/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_if.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 11:49:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/08 01:18:45 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

static void	clean_last_end_token(t_parser *parser)
{
	t_ast_token	*tmp;

	if (parser->pss->op_stack)
	{
		tmp = parser->pss->op_stack->next;
		free(parser->pss->op_stack->data);
		free(parser->pss->op_stack);
		if (!tmp)
			parser->pss->op_stack = NULL;
		else
			parser->pss->op_stack = tmp;
	}
}

int			rule_create_elif(t_parser *parser, t_ast_token *list)
{
	(void)parser;
	(void)list;
	return (0);
}

int			rule_close_if(t_parser *parser, t_ast_token *list)
{
	t_ast	*data;

	clean_last_end_token(parser);
	while (parser->pss->op_stack)
		add_to_ast_token_list(&parser->pss->output_queue,
				pop_ast_token(&parser->pss->op_stack));
	data = queue_to_ast(parser->pss);
	if (!data)
		return (1);
	free(list->data);
	parser->pss->ret->left = data;
	list->data = pss_pop(parser);
	list->type = TT_STATEMENT;
	return (0);
}
