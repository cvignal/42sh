/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 12:32:27 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/07 01:13:38 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ast.h"
#include "libft.h"

static const t_precedence	g_precedence[] =\
{
	{TT_PIPE, 2},
	{TT_END, 1},
	{TT_OR, 0},
	{TT_AND, 0},
	{TT_ARI_OP_PLUS, 0},
	{TT_ARI_OP_SUB, 0},
	{TT_ARI_OP_PROD, 1},
	{TT_ARI_OP_DIV, 1},
	{TT_ARI_OP_MOD, 1},
	{TT_ARI_OP_EQ, 2}
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

static int		set_leaves(t_ast *node, t_ast_token **stack)
{
	t_ast_token	*right;
	t_ast_token	*left;

	if (!node)
		return (1);
	if (!(right = pop_ast_token(stack)))
		return (1);
	if (!(left = pop_ast_token(stack)))
	{
		((t_ast *)right->data)->del(right->data);
		free(right);
		return (1);
	}
	node->right = right->data;
	node->left = left->data;
	free(right);
	free(left);
	return (0);
}

static t_ast	*clean_exit(t_pss *pss, t_ast_token *stack)
{
	pss->error = 1;
	free_input_queue(stack);
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

t_ast			*queue_to_ast(t_pss *pss)
{
	t_ast		*ret;
	t_ast_token	*stack;

	stack = NULL;
	while (pss->output_queue)
	{
		if (pss->output_queue->type == TT_OP)
		{
			if (set_leaves(pss->output_queue->data, &stack))
				return (clean_exit(pss, stack));
		}
		push_ast_token(&stack, pop_ast_token(&pss->output_queue));
	}
	if (stack)
	{
		if (stack->next)
			return (clean_exit(pss, stack));
		ret = stack->data;
		free(stack);
	}
	else
		return (NULL);
	return (ret);
}
