/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_if.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 11:49:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/07 08:56:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

static void	clean_last_end_token(t_parser *parser)
{
	t_ast_token	*token;

	token = parser->pss->output_queue;
	while (token->next->next)
		token = token->next;
	free(token->next->data);
	free(token->next);
	token->next = NULL;
}

int			rule_create_elif(t_parser *parser, t_ast_token *list)
{
	(void)parser;
	(void)list;
	return (0);
}

int			rule_close_if(t_parser *parser, t_ast_token *list)
{
	t_ast	*data;

	while (parser->pss->op_stack)
		add_to_ast_token_list(&parser->pss->output_queue,
				pop_ast_token(&parser->pss->op_stack));
	clean_last_end_token(parser);
	data = queue_to_ast(parser->pss);
	if (!data)
		return (1);
	free(list->data);
	parser->pss->ret->left = data;
	list->data = pss_pop(parser);
	list->type = TT_STATEMENT;
	return (0);
}
