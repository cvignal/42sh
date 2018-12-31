/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_else.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 13:58:35 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/31 17:03:19 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"
#include "ast.h"
#include "21sh.h"

int	rule_add_to_else(t_parser *parser, t_ast_token *list)
{
	t_ast_token	*tmp;
	t_ast		*node;
	t_ast		*iter;

	(void)parser;
	iter = list->data;
	while (iter->right)
		iter = iter->right;
	if (iter->left)
	{
		node = alloc_ast(NULL, TT_END, &exec_end, &free_end);
		if (!node)
			return (1);
		node->left = iter->left;
		node->right = list->next->data;
		iter->left = node;
	}
	else
		iter->left = list->next->data;
	tmp = list->next->next->next;
	free(list->next->next->data);
	free(list->next->next);
	free(list->next);
	list->next = tmp;
	return (0);
}

int	rule_create_else(t_parser *parser, t_ast_token *list)
{
	t_ast		*iter;
	t_ast_token	*tmp;
	t_ast		*node;

	(void)parser;
	node = alloc_ast(NULL, TT_ELSE, &exec_else, &free_else);
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
	list->state = PS_ELSE;
	list->pop = 1;
	return (0);
}
