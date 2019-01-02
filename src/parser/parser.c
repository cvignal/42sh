/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:36:20 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/02 10:53:39 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "21sh.h"
#include "libft.h"
#include "ast.h"
#include "libft.h"

static int			reduce(t_parser *parser, t_ast_token *input_queue)
{
	t_ast_act		act;

	if ((act = get_rule(input_queue, parser->pss
					? parser->pss->state : PS_NONE)))
	{
		if (act(parser, input_queue))
			return (2);
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

static int			get_return(t_parser *parser)
{
	if (parser->pss)
		return (PARSER_MORE_INPUT);
	else if (parser->input_queue->type == TT_STATEMENT
			&& parser->input_queue->next == NULL)
	{
		parser->ret = parser->input_queue->data;
		free(parser->input_queue);
		parser->input_queue = NULL;
		return (PARSER_COMPLETE);
	}
	else
	{
		free_input_queue(parser->input_queue);
		parser->input_queue = NULL;
		while (parser->pss)
			pss_pop(parser);
	}
	return (PARSER_EMPTY);
}

static int			get_parser_state(t_parser *parser, t_ast_token *token)
{
	if (parser->pss && token->pop)
		pss_pop(parser);
	if (token->state != PS_NONE)
		return (pss_push(parser, token->state));
	return (0);
}

int					parse(t_shell *shell, t_token *tokens)
{
	t_ast_token	*lookup_queue;
	int			did_reduce;

	add_to_ast_token_list(&shell->parser.input_queue, lookup(&tokens));
	did_reduce = 1;
	while (did_reduce)
	{
		did_reduce = 0;
		lookup_queue = shell->parser.input_queue;
		while (shell->parser.pss)
			pss_pop(&shell->parser);
		while (lookup_queue)
		{
			get_parser_state(&shell->parser, lookup_queue);
			if (reduce(&shell->parser, lookup_queue) == 1)
				did_reduce = 1;
			else
				lookup_queue = lookup_queue->next;
		}
	}
	return (get_return(&shell->parser));
}
