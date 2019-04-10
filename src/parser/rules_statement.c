/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_statement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 13:23:08 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 05:52:39 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "shell.h"
#include "libft.h"

int	rule_create_statement(t_parser *parser, t_ast_token *list)
{
	(void)parser;
	list->type = TT_STATEMENT;
	return (0);
}

int	rule_pop_cmd_statement(t_parser *parser, t_ast_token *list)
{
	t_ast_token		*new_token;
	t_command		*command;

	(void)list;
	new_token = alloc_ast_token(parser->pss->ret, TT_STATEMENT);
	if (!new_token)
		return (1);
	new_token->next = parser->input_queue;
	parser->input_queue = new_token;
	pss_pop(parser);
	command = ((t_ast *)parser->input_queue->data)->data;
	command->args_value = malloc(sizeof(*command->args_value)
			* (command->args_len + 1));
	if (!command->args_value)
		return (1);
	ft_bzero(command->args_value, sizeof(*command->args_value)
			* (command->args_len + 1));
	return (0);
}
