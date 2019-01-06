/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 20:36:36 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 03:49:14 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "21sh.h"

int	rule_or(t_parser *parser, t_ast_token *list)
{
	t_ast		*node;

	(void)parser;
	if (!(node = alloc_ast(list->next->data, TT_STATEMENT, exec_or, free_or)))
		return (1);
	free(list->data);
	list->data = node;
	list->type = TT_OP;
	return (0);
}

int	rule_and(t_parser *parser, t_ast_token *list)
{
	t_ast		*node;

	(void)parser;
	if (!(node = alloc_ast(list->next->data, TT_STATEMENT, exec_and, free_and)))
		return (1);
	free(list->data);
	list->data = node;
	list->type = TT_OP;
	return (0);
}
