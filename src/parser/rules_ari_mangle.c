/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_ari_mangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 06:04:29 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/13 07:05:11 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "arithmetic.h"

int	rule_ari_pre_mangle(t_parser *parser, t_token *list)
{
	t_token	*new_token;
	int			type;

	if (list->type == TT_ARI_OP_PLUS_PLUS)
		type = TT_ARI_OP_UPLUS;
	else
		type = TT_ARI_OP_USUB;
	if (!(new_token = alloc_ast_token(NULL, type)))
		return (1);
	list->type = type;
	new_token->next = parser->input_queue;
	parser->input_queue = new_token;
	return (0);
}

int	rule_ari_post_mangle(t_parser *parser, t_token *list)
{
	t_token	*new_token;
	int			type;

	if (list->next->type == TT_ARI_OP_PLUS_PLUS)
		type = TT_ARI_OP_UPLUS;
	else
		type = TT_ARI_OP_USUB;
	if (!(new_token = alloc_ast_token(NULL, type)))
		return (1);
	list->next->type = type;
	new_token->next = list->next;
	parser->input_queue->next = new_token;
	return (0);
}
