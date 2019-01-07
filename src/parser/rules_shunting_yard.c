/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_shunting_yard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 06:48:20 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/07 09:02:48 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "ast.h"

int	rule_send_to_shunting_yard(t_parser *parser, t_ast_token *list)
{
	(void)list;
	shunting_yard(parser);
	return (0);
}
