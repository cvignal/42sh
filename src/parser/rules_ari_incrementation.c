/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_ari_incrementation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 04:55:21 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/26 01:19:17 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "arithmetic.h"

int	rule_ari_post_plus_plus(t_parser *parser, t_token *list)
{
	t_ast	*ast_plus;
	t_token	*tmp;

	(void)parser;
	tmp = list->next->next;
	if (!(ast_plus = alloc_ast(tmp->data, TT_ARI_OP_PLUS_PLUS,
					&exec_ari_post_plus_plus, &free_ari)))
		return (1);
	tmp->data = ast_plus;
	tmp->type = TT_OP;
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	return (0);
}

int	rule_ari_pre_plus_plus(t_parser *parser, t_token *list)
{
	t_ast		*ast_plus;

	if (!(ast_plus = alloc_ast(list->data, TT_STATEMENT,
					&exec_ari_pre_plus_plus, &free_ari)))
		return (1);
	shift_token(parser, list, 0);
	free(parser->input_queue->data);
	parser->input_queue->data = ast_plus;
	parser->input_queue->type = TT_OP;
	return (0);
}
