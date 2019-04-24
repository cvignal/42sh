/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 12:32:27 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 17:27:51 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ast.h"
#include "parser.h"
#include "libft.h"

static const t_precedence	g_precedence[] =\
{
	{TT_PIPE, 2},
	{TT_END, 1},
	{TT_OR, 0},
	{TT_AND, 0}
};

static int		precedence(t_ttype type)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_precedence) / sizeof(*g_precedence))
	{
		if ((t_ttype)g_precedence[i].type == type)
			return (g_precedence[i].prec);
		++i;
	}
	return (-1);
}

static t_ast	*clean_exit(t_pss *pss)
{
	pss->status = PARSER_ERROR;
	free_input_queue(pss->stack);
	pss->stack = NULL;
	free_input_queue(pss->output_queue);
	pss->output_queue = NULL;
	free_input_queue(pss->op_stack);
	pss->op_stack = NULL;
	return (NULL);
}

void			shunting_yard(t_parser *parser)
{
	if (parser->input_queue->type == TT_OP)
	{
		while (parser->pss->op_stack
				&& precedence(((t_ast *)parser->input_queue->data)->type)
				<= precedence(((t_ast *)parser->pss->op_stack->data)->type))
			add_to_ast_token_list(&parser->pss->output_queue,
					pop_ast_token(&parser->pss->op_stack));
		push_ast_token(&parser->pss->op_stack,
				pop_ast_token(&parser->input_queue));
	}
	else if (parser->input_queue->type == TT_STATEMENT)
		add_to_ast_token_list(&parser->pss->output_queue,
				pop_ast_token(&parser->input_queue));
}

int				check_enough_tokens(t_pss *pss)
{
	if (!pss->stack)
		return (0);
	if (!pss->stack->next && ((t_ast *)pss->output_queue->data)->type != TT_END)
		return (0);
	return (1);
}

t_ast			*queue_to_ast(t_pss *pss)
{
	while (pss->output_queue)
	{
		if (pss->output_queue->type == TT_OP)
		{
			if (!check_enough_tokens(pss))
			{
				if (!pss->stack || pss->output_queue->next)
					return (clean_exit(pss));
				push_ast_token(&pss->op_stack
						, pop_ast_token(&pss->output_queue));
				pss->status = PARSER_MORE_INPUT;
				return (NULL);
			}
			if (set_leaves(pss->output_queue->data, &pss->stack))
				return (clean_exit(pss));
		}
		push_ast_token(&pss->stack, pop_ast_token(&pss->output_queue));
	}
	return (end_queue_to_ast(pss));
}
