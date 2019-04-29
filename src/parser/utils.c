/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 08:49:50 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/10 08:47:31 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"

void	shift_token(t_parser *parser, t_token *list, int del)
{
	if (del == 1)
		free(list->data);
	else if (del == 2)
		((t_ast *)list->data)->del(list->data);
	parser->input_queue = parser->input_queue->next;
	free(list);
}

void	clean_last_end_token(t_parser *parser)
{
	t_token	*tmp;

	if (parser->pss->op_stack)
	{
		tmp = parser->pss->op_stack->next;
		free(parser->pss->op_stack->data);
		free(parser->pss->op_stack);
		if (!tmp)
			parser->pss->op_stack = NULL;
		else
			parser->pss->op_stack = tmp;
	}
}
