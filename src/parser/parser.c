/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:36:20 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/10 06:54:25 by gchainet         ###   ########.fr       */
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
	int				did_reduce;

	did_reduce = 0;
	while (parser->input_queue
			&& (act = get_rule(parser->input_queue, parser->pss 
					? parser->pss->state : PS_NONE)))
	{
		if (act(parser, parser->input_queue))
			return (1);
		did_reduce = 1;
	}
	return (did_reduce ? 2 : 0);
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
	t_pss			*pss;

	ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, SYNTAX_ERROR_MSG);
	while (parser->pss->state != PS_NONE)
	{
		pss = parser->pss;
		parser->pss = parser->pss->next;
		free_input_queue(pss->output_queue);
		free_input_queue(pss->op_stack);
		if (pss->ret)
			((t_ast *)pss->ret)->del(pss->ret);
		free(pss);
	}
	free_input_queue(parser->input_queue);
	parser->input_queue = NULL;
	free_input_queue(parser->pss->output_queue);
	parser->pss->output_queue = NULL;
	free_input_queue(parser->pss->op_stack);
	parser->pss->op_stack = NULL;
	return (PARSER_EMPTY);
}

static int			get_return(t_parser *parser)
{
	t_ast	*ret;

	if (parser->pss->state != PS_NONE)
		return (PARSER_MORE_INPUT);
	else
	{
		if (parser->input_queue)
			return (clean_exit(parser));
		ret = queue_to_ast(parser->pss);
		if (!ret)
			return (clean_exit(parser));
	}
	parser->ret = ret;
	return (PARSER_COMPLETE);
}

int					parse(t_shell *shell, t_token *tokens)
{
	int				ret;

	add_to_ast_token_list(&shell->parser.input_queue, lookup(&tokens));
	while (shell->parser.input_queue)
	{
		if ((ret = reduce(&shell->parser)) == 1)
			return (clean_exit(&shell->parser));
		else if (!ret)
			return (clean_exit(&shell->parser));
	}
	if (shell->parser.pss->state != PS_NONE)
		return (get_return(&shell->parser));
	while (shell->parser.pss->op_stack)
		add_to_ast_token_list(&shell->parser.pss->output_queue,
				pop_ast_token(&shell->parser.pss->op_stack));
	return (get_return(&shell->parser));
}
