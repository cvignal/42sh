/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_if_nocd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 11:53:35 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/31 13:41:44 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

int	rule_create_if_nocd(t_parser *parser, t_ast_token *list)
{
	t_ast	*node;

	if (pss_push(parser, PS_IFNOCD))
		return (1);
	node = alloc_ast(NULL, TT_IF, &exec_if, &free_if);
	free(list->data);
	list->data = node;
	list->type = TT_IFNOCD;
	return (0);
}

int	rule_if_add_cd(t_parser *parser, t_ast_token *list)
{
	t_ast_token	*tmp;

	parser->pss->state = PS_IFCD;
	((t_ast *)list->data)->data = list->next->data;
	tmp = list->next->next->next->next;
	free(list->next->next->next->data);
	free(list->next->next->next);
	free(list->next->next->data);
	free(list->next->next);
	free(list->next);
	list->next = tmp;
	list->type = TT_IFCD;
	return (0);
}

int	rule_if_cd(t_parser *parser, t_ast_token *list)
{
	t_ast_token	*tmp;

	pss_pop(parser);
	if (pss_push(parser, PS_IFCD))
		return (1);
	tmp = list->next->next;
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	return (0);
}
