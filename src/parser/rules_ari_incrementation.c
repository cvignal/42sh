/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_ari_incrementation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 04:55:21 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/13 05:35:57 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "arithmetic.h"

int	rule_ari_post_plus_plus(t_parser *parser, t_ast_token *list)
{
	t_ast	*ast_plus;
	t_ast	*ast_value;

	if (!(ast_value = alloc_ast(list->data, TT_STATEMENT,
					&exec_ari_value, &free_ari)))
		return (1);
	if (!(ast_plus = alloc_ast(list->next->data, TT_STATEMENT,
					&exec_ari_post_plus_plus, &free_ari)))
		return (1);
	ast_plus->left = ast_value;
	list = list->next;
	free(parser->input_queue);
	parser->input_queue = list;
	parser->input_queue->data = ast_plus;
	parser->input_queue->type = TT_STATEMENT;
	return (0);
}

int	rule_ari_pre_plus_plus(t_parser *parser, t_ast_token *list)
{
	t_ast		*ast_plus;
	t_ast		*ast_value;
	t_ast_token	*tmp;

	(void)parser;
	if (!(ast_plus = alloc_ast(list->data, TT_STATEMENT,
					&exec_ari_pre_plus_plus, &free_ari)))
		return (1);
	if (!(ast_value = alloc_ast(list->next->data, TT_STATEMENT,
					&exec_ari_value, &free_ari)))
		return (1);
	ast_plus->left = ast_value;
	list->data = ast_plus;
	list->type = TT_STATEMENT;
	tmp = list->next->next;
	free(list->next);
	list->next = tmp;
	return (0);
}
