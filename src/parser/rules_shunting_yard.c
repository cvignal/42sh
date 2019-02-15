/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_shunting_yard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 06:48:20 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/15 17:50:17 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"

int	rule_send_to_shunting_yard(t_parser *parser, t_ast_token *list)
{
	if (list->type == TT_STATEMENT
			&& ((t_command *)((t_ast *)list->data)->data)->args_len == 0)
		return (1);
	shunting_yard(parser);
	return (0);
}
