/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 12:32:27 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 03:17:55 by gchainet         ###   ########.fr       */
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
		if ((t_ttype)g_precedence[i].type == type)
			return (g_precedence[i].prec);
	}
	return (-1);
}

static int	set_leaves(t_ast *node, t_ast_token **stack)
{
	t_ast_token	*right;
	t_ast_token	*left;

	if (!(right = pop_ast_token(stack)) || !(left = pop_ast_token(stack)))
	{
		if (right)
		{
			((t_ast *)right->data)->del(right->data);
			free(right);
		}
		free_ast(node);
	}
	node->right = right->data;
	node->left = left->data;
	free(right);
	free(left);
	return (0);
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
	t_ast		*ret;

	stack = NULL;
	while (queue)
	{
		tmp = queue->next;
		if (queue->type != TT_STATEMENT)
		{
			if (!queue || set_leaves(queue->data, &stack))
				return (NULL);
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
	return (parser->ret != NULL);
}
