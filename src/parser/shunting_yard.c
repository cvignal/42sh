/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 12:32:27 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/05 13:35:16 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ast.h"
#include "libft.h"

static const t_precedence	g_precedence[] =\
{
	{TT_PIPE, 0},
	{TT_END, 1},
	{TT_OR, 2},
	{TT_AND, 2}
};

static int	precedence(t_ttype type)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_precedence) / sizeof(*g_precedence))
	{
		if (g_precedence[i].type == type)
			return (g_precedence[i].prec);
	}
	return (-1);
}

static void	shunting_yard(t_parser *parser, t_ast_token **op,
		t_ast_token **output)
{
	while (*op
		|| precedence(parser->input_queue->type) <= precedence((*op)->type))
		add_to_ast_token_list(output, pop_ast_token(op));
}

static t_ast	*queue_to_ast(t_ast_token *queue)
{
	t_ast_token	*stack;
	t_ast_token	*tmp;
	t_ast_token	*pop;
	t_ast		*ret;

	stack = NULL;
	while (queue)
	{
		tmp = queue->next;
		if (queue->type != TT_STATEMENT)
		{
			pop = pop_ast_token(&stack);
			((t_ast *)queue->data)->left = pop->data;
			free(pop);
			pop = pop_ast_token(&stack);
			((t_ast *)queue->data)->right = pop->data;
			free(pop);
		}
		push_ast_token(&stack, queue);
		queue = tmp;
	}
	ret = stack->data;
	free(stack);
	return (ret);
}

int			build_ast(t_parser *parser)
{
	t_ast_token	*op_stack;
	t_ast_token	*output;
	t_ast_token	*tmp;

	op_stack = NULL;
	output = NULL;
	while (parser->input_queue)
	{
		tmp = parser->input_queue->next;
		if (parser->input_queue->type == TT_STATEMENT)
			add_to_ast_token_list(&output, parser->input_queue);
		else
			shunting_yard(parser, &op_stack, &output);
		parser->input_queue = tmp;
	}
	while (op_stack)
		add_to_ast_token_list(&output, op_stack);
	parser->ret = queue_to_ast(output);
	return (0);
}
