/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_while.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:51:02 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 09:39:30 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "parser.h"
#include "ast.h"

int	rule_create_while(t_parser *parser, t_ast_token *list)
{
	t_ast	*node;

	if (!(node = alloc_ast(NULL, TT_WHILE, &exec_while, &free_while)))
		return (1);
	pss_push(parser, PS_WHILENOCD, node);
	shift_ast_token(list, 1);
	return (0);
}

int	rule_while_add_cd(t_parser *parser, t_ast_token *list)
{

	parser->pss->state = PS_WHILECD;
	parser->pss->current->data = list->data;
	shift_ast_token(list, 0);
	shift_ast_token(list, 1);
	shift_ast_token(list, 1);
	return (0);
}

int	rule_while_add(t_parser *parser, t_ast_token *list)
{
	t_ast		*node;

	if (parser->pss->current->left)
	{
		node = alloc_ast(NULL, TT_END, &exec_end, &free_end);
		if (!node)
			return (1);
		node->left = parser->pss->current->left;
		node->right = list->data;
		parser->pss->current->left = node;
	}
	else
		parser->pss->current->left = list->data;
	shift_ast_token(list, 0);
	return (0);
}

int	rule_while_close(t_parser *parser, t_ast_token *list)
{
	free(list->data);
	list->data = pss_pop(parser);
	list->type = TT_STATEMENT;
	return (0);
}
