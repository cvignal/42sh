/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:36:20 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 10:35:38 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "21sh.h"
#include "libft.h"
#include "ast.h"
#include "libft.h"

static int			reduce(t_parser *parser)
{
	t_ast_act		act;
	t_ast_token		*lookup;

	lookup = parser->input_queue;
	while (parser->input_queue
			&& (act = get_rule(lookup, parser->pss 
					? parser->pss->state : PS_NONE)))
	{
		if (act(parser, lookup))
			return (1);
	}
	return (0);
}

static t_ast_token	*lookup(t_token **tokens)
{
	t_ast_token	*input_queue;
	t_ast_token	*new_token;
	t_token		*tmp;

	input_queue = NULL;
	while ((tmp = *tokens))
	{
		if (!(new_token = alloc_ast_token(tmp->data, tmp->type)))
			return (NULL);
		add_to_ast_token_list(&input_queue, new_token);
		*tokens = (*tokens)->next;
		free(tmp);
	}
	return (input_queue);
}

static int			clean_exit(t_parser *parser)
{
	ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, SYNTAX_ERROR_MSG);
	free_input_queue(parser->input_queue);
	free_input_queue(parser->output_queue);
	free_input_queue(parser->op_stack);
	while (parser->pss)
		pss_pop(parser);
	ft_bzero(parser, sizeof(*parser));
	return (PARSER_EMPTY);
}

static int			get_return(t_parser *parser)
{
	t_ast	*ret;

	if (parser->pss)
		return (PARSER_MORE_INPUT);
	else
	{
		ret = queue_to_ast(parser);
		if (!ret)
			return (PARSER_EMPTY);
		if (parser->input_queue)
			return (clean_exit(parser));
	}
	ft_bzero(parser, sizeof(*parser));
	parser->ret = ret;
	return (PARSER_COMPLETE);
}

int					parse(t_shell *shell, t_token *tokens)
{
	add_to_ast_token_list(&shell->parser.input_queue, lookup(&tokens));
	while (shell->parser.input_queue)
	{
		if (reduce(&shell->parser) == 1)
			return (clean_exit(&shell->parser));
		if (shell->parser.input_queue
				&& shell->parser.input_queue->type == TT_STATEMENT)
			add_to_ast_token_list(&shell->parser.output_queue,
					pop_ast_token(&shell->parser.input_queue));
		else if (shell->parser.input_queue
				&& shell->parser.input_queue->type == TT_OP)
			shunting_yard(&shell->parser);
		else
			return (get_return(&shell->parser));
	}
	while (shell->parser.op_stack)
		add_to_ast_token_list(&shell->parser.output_queue,
				pop_ast_token(&shell->parser.op_stack));
	return (get_return(&shell->parser));
}
