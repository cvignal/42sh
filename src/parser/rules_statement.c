/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_statement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 13:23:08 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/29 18:40:33 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	rule_create_statement(t_parser *parser, t_ast_token *list)
{
	(void)parser;
	list->type = TT_STATEMENT;
	return (0);
}
