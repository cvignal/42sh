/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_ari_decrementation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 05:55:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/26 01:28:39 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "arithmetic.h"

int	rule_ari_post_sub_sub(t_parser *parser, t_token *list)
{
	t_ast	*ast_sub;
	t_token	*tmp;

	(void)parser;
	tmp = list->next->next;
	if (!(ast_sub = alloc_ast(tmp->data, TT_ARI_OP_SUB_SUB,
					&exec_ari_post_sub_sub, &free_ari)))
		return (1);
	tmp->data = ast_sub;
	tmp->type = TT_OP;
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	return (0);
}

int	rule_ari_pre_sub_sub(t_parser *parser, t_token *list)
{
	t_ast		*ast_sub;

	if (!(ast_sub = alloc_ast(list->data, TT_ARI_OP_SUB_SUB,
					&exec_ari_pre_sub_sub, &free_ari)))
		return (1);
	shift_token(parser, list, 0);
	free(parser->input_queue->data);
	parser->input_queue->data = ast_sub;
	parser->input_queue->type = TT_OP;
	return (0);
}
