/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_if_nocd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 11:53:35 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 10:20:02 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

int	rule_create_elif_nocd(t_parser *parser, t_ast_token *list)
{
	t_ast		*node;
	t_ast		*iter;

	parser->pss->state = PS_IFNOCD;
	if (!(node = alloc_ast(NULL, TT_IF, &exec_if, &free_if)))
		return (1);
	iter = parser->pss->current->data;
	while (iter->right)
		iter = iter->right;
	iter->right = node;
	shift_ast_token(list, 1);
	return (0);
}

int	rule_create_if_nocd(t_parser *parser, t_ast_token *list)
{
	t_ast	*node;

	if (!(node = alloc_ast(NULL, TT_IF, &exec_if, &free_if)))
		return (1);
	pss_push(parser, PS_IFNOCD, node);
	shift_ast_token(list, 1);
	return (0);
}

int	rule_if_add_cd(t_parser *parser, t_ast_token *list)
{
	t_ast		*iter;

	parser->pss->state = PS_IFCD;
	iter = parser->pss->current;
	while (iter->right)
		iter = iter->right;
	iter->data = list->data;
	shift_ast_token(list, 0);
	shift_ast_token(list, 1);
	shift_ast_token(list, 1);
	return (0);
}
