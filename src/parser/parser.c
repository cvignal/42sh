/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:36:20 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/31 12:35:04 by gchainet         ###   ########.fr       */
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

int					init_parser(t_parser *parser)
{
	ft_bzero(parser, sizeof(*parser));
	return (0);
}

static void		debug_iq(t_ast_token *input)
{
	while (input)
	{
		ft_printf("%d ", input->type);
		input = input->next;
	}
	ft_printf("\n");
}

int					parse(t_shell *shell, t_token *tokens)
{
	t_ast_token	*lookup_queue;
	int			did_reduce;

	if (!tokens)
		return (PARSER_EMPTY);
	add_to_ast_token_list(&shell->parser.input_queue, lookup(&tokens));
	did_reduce = 1;
	debug_iq(shell->parser.input_queue);
	while (did_reduce)
	{
		did_reduce = 0;
		lookup_queue = shell->parser.input_queue;
		while (lookup_queue)
		{
			if (reduce(&shell->parser, lookup_queue) == 1)
			{
				did_reduce = 1;
				debug_iq(shell->parser.input_queue);
			}
			else
				lookup_queue = lookup_queue->next;
		}
	}
	return (get_return(&shell->parser));
}
