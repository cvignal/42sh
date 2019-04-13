/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 12:32:27 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/13 03:46:46 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ast.h"
#include "libft.h"

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

static void		shunting_yard_parenthesis(t_parser *parser)
{
	if (parser->input_queue->type == TT_CLOSE_PAR)
	{
		pop_ast_token(&parser->input_queue);
		while (parser->pss->op_stack
				&& parser->pss->op_stack->type != TT_OPEN_PAR)
			add_to_ast_token_list(&parser->pss->output_queue,
					pop_ast_token(&parser->pss->op_stack));
		if (parser->pss->op_stack)
			pop_ast_token(&parser->pss->op_stack);
		else
			clean_exit(parser->pss, NULL);
	}
	else if (parser->input_queue->type == TT_OPEN_PAR)
		push_ast_token(&parser->pss->op_stack,
				pop_ast_token(&parser->input_queue));
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
	else
		shunting_yard_parenthesis(parser);
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
