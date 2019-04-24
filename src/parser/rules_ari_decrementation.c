/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_ari_decrementation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 05:55:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/13 05:56:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "arithmetic.h"

int	rule_ari_post_sub_sub(t_parser *parser, t_token *list)
{
	t_ast	*ast_sub;
	t_ast	*ast_value;

	if (!(ast_value = alloc_ast(list->data, TT_STATEMENT,
					&exec_ari_value, &free_ari)))
		return (1);
	if (!(ast_sub = alloc_ast(list->next->data, TT_STATEMENT,
					&exec_ari_post_sub_sub, &free_ari)))
		return (1);
	ast_sub->left = ast_value;
	list = list->next;
	free(parser->input_queue);
	parser->input_queue = list;
	parser->input_queue->data = ast_sub;
	parser->input_queue->type = TT_STATEMENT;
	return (0);
}

int	rule_ari_pre_sub_sub(t_parser *parser, t_token *list)
{
	t_ast		*ast_sub;
	t_ast		*ast_value;
	t_token	*tmp;

	(void)parser;
	if (!(ast_sub = alloc_ast(list->data, TT_STATEMENT,
					&exec_ari_pre_sub_sub, &free_ari)))
		return (1);
	if (!(ast_value = alloc_ast(list->next->data, TT_STATEMENT,
					&exec_ari_value, &free_ari)))
		return (1);
	ast_sub->left = ast_value;
	list->data = ast_sub;
	list->type = TT_STATEMENT;
	tmp = list->next->next;
	free(list->next);
	list->next = tmp;
	return (0);
}
