/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 20:36:36 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/02 13:18:56 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "libft.h"
#include "21sh.h"

int	rule_or(t_parser *parser, t_ast_token *list)
{
	t_ast		*node;
	t_ast_token	*tmp;

	(void)parser;
	if (!(node = alloc_ast(list->next->data, TT_STATEMENT, exec_or, free_or)))
		return (1);
	node->left = list->data;
	node->right = list->next->next->data;
	tmp = list->next->next->next;
	free(list->next->next);
	free(list->next);
	list->next = tmp;
	list->data = node;
	return (0);
}

int	rule_and(t_parser *parser, t_ast_token *list)
{
	t_ast		*node;
	t_ast_token	*tmp;

	(void)parser;
	if (!(node = alloc_ast(list->next->data, TT_STATEMENT, exec_and, free_and)))
		return (1);
	node->left = list->data;
	node->right = list->next->next->data;
	tmp = list->next->next->next;
	free(list->next->next);
	free(list->next);
	list->next = tmp;
	list->data = node;
	return (0);
}
