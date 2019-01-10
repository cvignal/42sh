/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_while.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:51:02 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/10 06:07:23 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "parser.h"
#include "ast.h"

int	rule_create_while(t_parser *parser, t_ast_token *list)
{
	t_ast	*node;

	node = alloc_ast(NULL, TT_WHILE, &exec_while, &free_while);
	if (!node)
		return (1);
	if (pss_push(parser, PS_WHILENOCD | PS_NONE))
	{
		free(node);
		return (1);
	}
	parser->pss->ret = node;
	shift_ast_token(parser, list, 1);
	return (0);
}

int	rule_while_add_cd(t_parser *parser, t_ast_token *list)
{
	if (parser->pss->ret->data)
		return (1);
	parser->pss->ret->data = list->data;
	shift_ast_token(parser, list, 0);
	return (0);
}

int	rule_while_close_cd(t_parser *parser, t_ast_token *list)
{
	if (!parser->pss->ret->data)
		return (1);
	parser->pss->state = PS_WHILECD | PS_NONE;
	shift_ast_token(parser, list, 1);
	return (0);
}

int	rule_while_close(t_parser *parser, t_ast_token *list)
{
	t_ast	*data;

	clean_last_end_token(parser);
	while (parser->pss->op_stack)
		add_to_ast_token_list(&parser->pss->output_queue,
				pop_ast_token(&parser->pss->op_stack));
	data = queue_to_ast(parser->pss);
	if (!data)
		return (1);
	parser->pss->ret->left = data;
	free(list->data);
	list->data = pss_pop(parser);
	list->type = TT_STATEMENT;
	return (0);
}
