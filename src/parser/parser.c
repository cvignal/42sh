/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:36:20 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 02:05:19 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "libft.h"
#include "ast.h"
#include "libft.h"

static int			reduce(t_parser *parser)
{
	t_ast_act		act;
	int				did_reduce;

	did_reduce = 0;
	while (parser->input_queue
			&& (act = get_rule(parser->input_queue, parser->pss->state)))
	{
		if (act(parser, parser->input_queue))
			return (1);
		did_reduce = 1;
	}
	return (did_reduce ? 2 : 0);
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
	return (PARSER_ERROR);
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
		if (parser->pss->status == PARSER_ERROR)
			return (clean_exit(parser));
		else if (parser->pss->status == PARSER_MORE_INPUT)
			return (PARSER_MORE_INPUT);
	}
	if ((parser->ret = ret))
		return (PARSER_COMPLETE);
	else
		return (PARSER_EMPTY);
}

int					parse(t_shell *shell, t_token *tokens)
{
	int				ret;

	shell->parser.pss->status = PARSER_EMPTY;
	shell->parser.input_queue = tokens;
	while (shell->parser.input_queue)
	{
		if ((ret = reduce(&shell->parser)) == 1)
			return ((shell->parser.ret_status = clean_exit(&shell->parser)));
		else if (!ret)
			return ((shell->parser.ret_status = clean_exit(&shell->parser)));
	}
	if (shell->parser.pss->state != PS_NONE)
		return ((shell->parser.ret_status = get_return(&shell->parser)));
	while (shell->parser.pss->op_stack)
		add_to_ast_token_list(&shell->parser.pss->output_queue,
				pop_ast_token(&shell->parser.pss->op_stack));
	return ((shell->parser.ret_status = get_return(&shell->parser)));
}
