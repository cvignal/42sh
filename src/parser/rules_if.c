/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_if.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 11:49:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 09:38:48 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

int	rule_add_to_if(t_parser *parser, t_ast_token *list)
{
	t_ast		*node;
	t_ast		*iter;

	iter = parser->pss->current;
	while (iter->right)
		iter = iter->right;
	if (iter->left)
	{
		if (!(node = alloc_ast(NULL, TT_END, &exec_end, &free_end)))
			return (1);
		node->left = iter->left;
		node->right = list->data;
		iter->left = node;
	}
	else
		iter->left = list->data;
	shift_ast_token(list, 0);
	return (0);
}

int	rule_create_elif(t_parser *parser, t_ast_token *list)
{
	t_ast		*node;
	t_ast		*iter;

	parser->pss->state = PS_IFNOCD;
	node = alloc_ast(list->next->data, TT_ELIF, &exec_if, &free_if);
	if (!node)
		return (1);
	iter = parser->pss->current;
	while (iter->right)
		iter = iter->right;
	iter->right = node;
	shift_ast_token(list, 1);
	return (0);
}

int	rule_close_if(t_parser *parser, t_ast_token *list)
{
	free(list->data);
	list->data = pss_pop(parser);
	list->type = TT_STATEMENT;
	return (0);
}
