/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 12:32:27 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/23 23:17:30 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ast.h"
#include "parser.h"
#include "libft.h"

static int		set_leaves(t_ast *node, t_token **stack)
{
	t_token	*right;
	t_token	*left;

	if (!node)
		return (1);
	right = pop_ast_token(stack);
	node->right = right->data;
	free(right);
	node->left = NULL;
	if (!(left = pop_ast_token(stack)))
	{
		if (node->type == TT_END)
			return (0);
		((t_ast *)right->data)->del(right->data);
		free(right);
		return (1);
	}
	node->left = left->data;
	free(left);
	return (0);
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

static void		shunting_yard_parenthesis(t_parser *parser)
{
	if (parser->input_queue->type == TT_CLOSE_PAR)
	{
		free_ast_token(pop_ast_token(&parser->input_queue));
		while (parser->pss->op_stack
				&& parser->pss->op_stack->type != TT_OPEN_PAR)
			add_to_ast_token_list(&parser->pss->output_queue,
					pop_ast_token(&parser->pss->op_stack));
		if (parser->pss->op_stack)
			free_ast_token(pop_ast_token(&parser->pss->op_stack));
		else
			clean_exit(parser->pss);
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


int check_enough_tokens(t_pss *pss)
{
	if (!pss->stack)
		return (0);
	if (!pss->stack->next && ((t_ast *)pss->output_queue->data)->type != TT_END)
		return (0);
	return (1);
}

t_ast			*queue_to_ast(t_pss *pss)
{
	t_ast		*ret;
	
	while (pss->output_queue)
	{
		if (pss->output_queue->type == TT_OP)
		{
			if (!check_enough_tokens(pss))
			{
				if (!pss->stack || pss->output_queue->next)
					return (clean_exit(pss));
				push_ast_token(&pss->op_stack, pop_ast_token(&pss->output_queue));
				pss->status = PARSER_MORE_INPUT;
				return (NULL);
			}
			if (set_leaves(pss->output_queue->data, &pss->stack))
				return (clean_exit(pss));
		}
		push_ast_token(&pss->stack, pop_ast_token(&pss->output_queue));
	}
	if (pss->stack)
	{
		if (pss->stack->next)
			return (clean_exit(pss));
		ret = pss->stack->data;
		free(pss->stack);
		pss->stack = NULL;
	}
	else
		return (NULL);
	pss->status = PARSER_COMPLETE;
	return (ret);
}
