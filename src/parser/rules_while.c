/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_while.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:51:02 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/31 18:26:52 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "parser.h"
#include "ast.h"

int	rule_create_while(t_parser *parser, t_ast_token *list)
{
	t_ast	*node;

	(void)parser;
	if (!(node = alloc_ast(NULL, TT_WHILE, &exec_while, &free_while)))
		return (1);
	free(list->data);
	list->data = node;
	list->type = TT_WHILENOCD;
	list->state = PS_WHILENOCD;
	return (0);
}

int	rule_while_add_cd(t_parser *parser, t_ast_token *list)
{
	t_ast_token	*tmp;

	(void)parser;
	((t_ast *)list->data)->data = list->next->data;
	tmp = list->next->next->next->next;
	free(list->next->next->next->data);
	free(list->next->next->next);
	free(list->next->next->data);
	free(list->next->next);
	free(list->next);
	list->next = tmp;
	list->state = PS_WHILECD;
	list->type = TT_WHILECD;
	list->pop = 1;
	return (0);
}

int	rule_while_add(t_parser *parser, t_ast_token *list)
{
	t_ast_token	*tmp;
	t_ast		*node;

	(void)parser;
	if (((t_ast *)list->data)->left)
	{
		node = alloc_ast(NULL, TT_END, &exec_end, &free_end);
		if (!node)
			return (1);
		node->left = ((t_ast *)list->data)->left;
		node->right = list->next->data;
		((t_ast *)list->data)->left = node;
	}
	else
		((t_ast *)list->data)->left = list->next->data;
	tmp = list->next->next;
	free(list->next);
	list->next = tmp;
	list->pop = 1;
	return (0);
}

int	rule_while_close(t_parser *parser, t_ast_token *list)
{
	t_ast_token	*tmp;

	(void)parser;
	tmp = list->next->next;
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	list->pop = 1;
	list->state = PS_NONE;
	list->type = TT_STATEMENT;
	return (0);
}
