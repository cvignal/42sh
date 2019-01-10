/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_if.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 11:49:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/10 07:09:08 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "ast.h"

static int	pop_if(t_parser *parser)
{
	clean_last_end_token(parser);
	while (parser->pss->op_stack)
		add_to_ast_token_list(&parser->pss->output_queue,
				pop_ast_token(&parser->pss->op_stack));
	parser->pss->ret->left = queue_to_ast(parser->pss);
	if (!parser->pss->ret->left)
		return (1);
	if (parser->input_queue->type == TT_STATEMENT)
		parser->pss->ret->right = parser->input_queue->data;
	parser->input_queue->data = pss_pop(parser);
	parser->input_queue->type = TT_STATEMENT;
	return (0);
}

int			rule_elif(t_parser *parser, t_ast_token *list)
{
	t_ast	*node;

	node = alloc_ast(NULL, TT_ELIF, &exec_if, &free_if);
	if (!node || pss_push(parser, PS_IFNOCD | PS_NONE))
		return (1);
	parser->pss->ret = node;
	shift_ast_token(parser, list, 1);
	return (0);
}

int			rule_close_if(t_parser *parser, t_ast_token *list)
{
	free(list->data);
	if (parser->pss->ret->type == TT_ELSE && pop_if(parser))
		return (1);
	while (parser->pss->ret->type == TT_ELIF)
		if (pop_if(parser))
			return (1);
	if (pop_if(parser))
		return (1);
	return (0);
}

int			rule_else(t_parser *parser, t_ast_token *list)
{
	t_ast	*node;

	node = alloc_ast(NULL, TT_ELSE, &exec_else, &free_else);
	if (!node || pss_push(parser, PS_IFCD | PS_NONE))
		return (1);
	parser->pss->ret = node;
	shift_ast_token(parser, list, 1);
	return (0);
}
