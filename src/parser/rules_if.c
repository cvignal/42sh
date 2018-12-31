/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_if.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 11:49:38 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/31 17:29:05 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

int	rule_add_to_if(t_parser *parser, t_ast_token *list)
{
	t_ast		*node;
	t_ast_token	*tmp;
	t_ast		*iter;

	(void)parser;
	iter = list->data;
	while (iter->right)
		iter = iter->right;
	if (iter->left)
	{
		if (!(node = alloc_ast(NULL, TT_END, &exec_end, &free_end)))
			return (1);
		node->left = iter->left;
		node->right = list->next->data;
		iter->left = node;
	}
	else
		iter->left = list->next->data;
	tmp = list->next->next;
	free(list->next);
	list->next = tmp;
	return (0);
}

int	rule_create_elif(t_parser *parser, t_ast_token *list)
{
	t_ast		*node;
	t_ast		*iter;
	t_ast_token	*tmp;

	(void)parser;
	node = alloc_ast(list->next->next->data, TT_ELIF, &exec_if, &free_if);
	if (!node)
		return (1);
	iter = list->data;
	while (iter->right)
		iter = iter->right;
	iter->right = node;
	tmp = list->next->next;
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	list->state = PS_IFNOCD;
	list->pop = 1;
	return (0);
}

int	rule_close_if(t_parser *parser, t_ast_token *list)
{
	t_ast_token	*tmp;

	(void)parser;
	tmp = list->next->next;
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	list->type = TT_STATEMENT;
	list->state = PS_NONE;
	return (0);
}
