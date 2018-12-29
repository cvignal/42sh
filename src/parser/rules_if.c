/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_if.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 11:49:38 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/29 17:31:08 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

int	rule_create_if(t_ast_token *list)
{
	t_ast		*node;
	t_ast_token	*tmp;

	node = alloc_ast(list->next->data, TT_IF, &exec_if, &free_if);
	if (!node)
		return (1);
	tmp = list->next->next->next->next;
	free(list->next->next->next->data);
	free(list->next->next->next);
	free(list->next->next->data);
	free(list->next->next);
	free(list->next);
	list->next = tmp;
	list->type = TT_IFCD;
	list->data = node;
	return (0);
}

int	rule_add_to_if(t_ast_token *list)
{
	t_ast		*node;
	t_ast_token	*tmp;

	node = alloc_ast(NULL, TT_END, &exec_end, &free_end);
	if (!node)
		return (1);
	node->left = ((t_ast *)list->data)->left;
	node->right = list->next->data;
	((t_ast *)list->data)->left = node;
	tmp = list->next->next->next;
	free(list->next->next->data);
	free(list->next->next);
	free(list->next);
	list->next = tmp;
	return (0);
}

int	rule_create_elif(t_ast_token *list)
{
	t_ast		*node;
	t_ast		*iter;
	t_ast_token	*tmp;

	node = alloc_ast(list->next->next->data, TT_ELIF, &exec_if, &free_if);
	if (!node)
		return (1);
	iter = list->data;
	while (iter->left && iter->left->type == TT_ELIF)
	{
		if (iter->right)
			return (1);
		iter = iter->left;
	}
	iter->left = node;
	tmp = list->next->next->next;
	free(list->next->next);
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	return (0);
}

int	rule_create_else(t_ast_token *list)
{
	t_ast		*iter;
	t_ast_token	*tmp;
	t_ast		*node;

	node = alloc_ast(NULL, TT_ELSE, &exec_else, &free_else);
	if (!node)
		return (1);
	iter = list->data;
	while (iter && (iter->type == TT_IF || iter->type == TT_ELIF))
	{
		iter->right = node;
		iter = iter->left;
	}
	tmp = list->next->next;
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	return (0);
}

int	rule_close_if(t_ast_token *list)
{
	t_ast_token	*tmp;

	tmp = list->next->next;
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	list->type = TT_STATEMENT;
	return (0);
}
