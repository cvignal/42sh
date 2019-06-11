/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 20:36:36 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 05:53:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "shell.h"

int	rule_or(t_parser *parser, t_token *list)
{
	t_ast		*node;

	(void)parser;
	if (!(node = alloc_ast(NULL, TT_OR, exec_or, free_ast_both)))
		return (1);
	free(list->data);
	list->data = node;
	list->type = TT_OP;
	return (0);
}

int	rule_and(t_parser *parser, t_token *list)
{
	t_ast		*node;

	(void)parser;
	if (!(node = alloc_ast(NULL, TT_AND, exec_and, free_ast_both)))
		return (1);
	free(list->data);
	list->data = node;
	list->type = TT_OP;
	return (0);
}
