/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_ari_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:02:02 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/26 20:36:53 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"

int	rule_ari_op(t_parser *parser, t_token *list)
{
	t_ast			*node;
	t_ari_op_desc	desc;

	(void)parser;
	if (get_arithmetic_desc(list->type, &desc))
		return (1);
	if (!(node = alloc_ast(list->data, list->type, desc.exec, desc.del)))
		return (1);
	list->data = node;
	list->type = TT_OP;
	return (0);
}
