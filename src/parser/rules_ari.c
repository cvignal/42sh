/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_ari.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 23:51:03 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/13 08:38:15 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"

int	rule_create_ari_statement(t_parser *parser, t_ast_token *list)
{
	t_ast	*ast;

	(void)parser;
	if (!(ast = alloc_ast(list->data, TT_STATEMENT, &exec_ari_statement,
					&free_ari_statement)))
		return (1);
	list->data = ast;
	list->type = TT_STATEMENT;
	return (0);
}

int	rule_create_ari_id(t_parser *parser, t_ast_token *list)
{
	t_ast	*ast;

	(void)parser;
	if (!(ast = alloc_ast(list->data, list->type, &exec_ari_value,
					&free_ari)))
		return (1);
	list->data = ast;
	list->type = TT_STATEMENT;
	return (0);
}

int	rule_ari_over(t_parser *parser, t_ast_token *list)
{
	while (parser->pss->op_stack)
		add_to_ast_token_list(&parser->pss->output_queue,
				pop_ast_token(&parser->pss->op_stack));
	free(list->data);
	list->data = queue_to_ast(parser->pss);
	list->type = TT_STATEMENT;
	pss_pop(parser);
	return (0);
}
