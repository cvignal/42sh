/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_expr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 12:44:48 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/26 18:35:14 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "parser.h"
#include "21sh.h"

int	rule_create_expr(t_ast_token *list)
{
	t_ast		*node;
	t_expr		*expr;

	expr = alloc_expr();
	if (!expr)
		return (1);
	node = alloc_ast(expr, TT_EXPR, &exec_expr, &free_expr);
	if (!node)
	{
		free(expr);
		return (1);
	}
	list->type = TT_EXPR_INCOMPLETE;
	free(list->data);
	list->data = node;
	return (0);
}

int	rule_add_to_expr(t_ast_token *list)
{
	t_ast_token	*tmp;

	if (add_to_expr(((t_ast *)list->data)->data, list->next->data))
		return (1);
	tmp = list->next->next;
	free(list->next);
	list->next = tmp;
	return (0);
}

int	rule_close_expr(t_ast_token *list)
{
	t_ast_token	*tmp;

	tmp = list->next->next;
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	list->type = TT_EXPR;
	return (0);
}
