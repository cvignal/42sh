/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_expr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 12:44:48 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/09 11:43:50 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "parser.h"
#include "21sh.h"

int	rule_create_expr(t_parser *parser, t_ast_token *list)
{
	if (pss_push(parser, PS_EXPR))
		return (1);
	shift_ast_token(parser, list, 1);
	return (0);
}

int	rule_make_expr(t_parser *parser, t_ast_token *list)
{
	t_ast		*node;
	t_expr		*expr;

	(void)parser;
	if ((list->type = keyword_type(list->data)) != TT_WORD)
		return (0);
	if (!(expr = alloc_expr()))
		return (1);
	if (!(node = alloc_ast(expr, TT_EXPR, &exec_expr, &free_expr)))
	{
		free(expr);
		return (1);
	}
	if (add_to_expr(expr, list->data))
	{
		free(expr);
		free(node);
		return (1);
	}
	list->data = node;
	list->type = TT_EXPR;
	return (0);
}

int	rule_add_to_expr(t_parser *parser, t_ast_token *list)
{
	t_ast_token	*tmp;

	(void)parser;
	if ((list->next->type = keyword_type(list->next->data)) != TT_WORD)
		return (0);
	if (add_to_expr(((t_ast *)list->data)->data, list->next->data))
		return (1);
	tmp = list->next->next;
	free(list->next);
	list->next = tmp;
	return (0);
}

int	rule_close_expr(t_parser *parser, t_ast_token *list)
{
	t_ast	*data;

	while (parser->pss->op_stack)
		add_to_ast_token_list(&parser->pss->output_queue,
				pop_ast_token(&parser->pss->op_stack));
	data = queue_to_ast(parser->pss);
	if (!data)
		return (1);
	pss_pop(parser);
	free(list->data);
	list->data = data;
	list->type = TT_STATEMENT;
	return (0);
}
