/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_if_nocd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 11:53:35 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/31 16:54:48 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

int	rule_create_elif_nocd(t_parser *parser, t_ast_token *list)
{
	t_ast		*node;
	t_ast		*iter;
	t_ast_token	*tmp;

	(void)parser;
	if (!(node = alloc_ast(NULL, TT_IF, &exec_if, &free_if)))
		return (1);
	iter = list->data;
	while (iter->right)
		iter = iter->right;
	iter->right = node;
	tmp = list->next->next;
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	list->type = TT_IFNOCD;
	list->state = PS_IFNOCD;
	return (0);
}

int	rule_create_if_nocd(t_parser *parser, t_ast_token *list)
{
	t_ast	*node;

	(void)parser;
	if (!(node = alloc_ast(NULL, TT_IF, &exec_if, &free_if)))
		return (1);
	free(list->data);
	list->data = node;
	list->type = TT_IFNOCD;
	list->state = PS_IFNOCD;
	return (0);
}

int	rule_if_add_cd(t_parser *parser, t_ast_token *list)
{
	t_ast_token	*tmp;
	t_ast		*iter;

	(void)parser;
	iter = list->data;
	while (iter->right)
		iter = iter->right;
	iter->data = list->next->data;
	tmp = list->next->next->next->next;
	free(list->next->next->next->data);
	free(list->next->next->next);
	free(list->next->next->data);
	free(list->next->next);
	free(list->next);
	list->next = tmp;
	list->type = TT_IFCD;
	list->state = PS_IFCD;
	list->pop = 1;
	return (0);
}
