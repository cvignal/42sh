/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_shunting_yard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 06:48:20 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/26 20:13:52 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"

int	rule_send_to_shunting_yard(t_parser *parser, t_token *list)
{
	if (!(parser->pss->state & PS_ARI))
	{
		if (list->type == TT_STATEMENT
				|| ((t_ast *)list->data)->type == TT_END_UNARY)
			parser->pss->status = PARSER_COMPLETE;
		else if (list->type == TT_OP)
		{
			if (parser->pss->status == PARSER_MORE_INPUT)
			{
				parser->pss->status = PARSER_ERROR;
				return (1);
			}
			parser->pss->status = PARSER_MORE_INPUT;
		}
	}
	shunting_yard(parser);
	return (0);
}
