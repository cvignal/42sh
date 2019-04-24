/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_shunting_yard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 06:48:20 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 18:24:40 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"

int	rule_send_to_shunting_yard(t_parser *parser, t_token *list)
{
	(void)list;
	if (list->type == TT_STATEMENT)
		parser->pss->status = PARSER_COMPLETE;
	else if (list->type == TT_OP
			&& ((t_ast *)list->data)->type != TT_END_UNARY)
		parser->pss->status = PARSER_MORE_INPUT;
	shunting_yard(parser);
	return (0);
}
