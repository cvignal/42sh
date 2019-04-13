/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_ari_usub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 06:12:31 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/13 06:30:31 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	rule_ari_create_usub(t_parser *parser, t_ast_token *list)
{
	t_ast	*ast;

	(void)parser;
	ast = alloc_ast(list->data, TT_ARI_OP_USUB, &exec_ari_usub, &free_ari);
	if (!ast)
		return (1);
	list->data = ast;
	list->type = TT_OP;
	return (0);
}
