/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 12:32:27 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/27 19:01:52 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ast.h"
#include "parser.h"
#include "libft.h"

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

static int		valid_token(const t_op_prop *input_op_prop
		, const t_op_prop *stack_op_prop)
{
	if ((input_op_prop->asso == LEFT && input_op_prop->precedence
			<= stack_op_prop->precedence) || (input_op_prop->asso
				== RIGHT && input_op_prop->precedence
					< stack_op_prop->precedence))
		return (1);
	else
		return (0);
}

void			shunting_yard(t_parser *parser)
{
	const t_op_prop	*input_op_prop;
	const t_op_prop	*stack_op_prop;

	if (parser->input_queue->type == TT_OP)
	{
		input_op_prop = get_op_prop(((t_ast *)parser->input_queue->data)->type);
		while (parser->pss->op_stack)
		{
			if (!(stack_op_prop = get_op_prop(((t_ast *)parser->pss\
								->op_stack->data)->type)))
				break ;
			if (valid_token(input_op_prop, stack_op_prop))
				add_to_ast_token_list(&parser->pss->output_queue,
						pop_ast_token(&parser->pss->op_stack));
			else
				break ;
		}
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

	while (pss->output_queue)
	{
		if (pss->output_queue->type == TT_OP)
			if (set_leaves(pss->output_queue->data, &pss->stack))
				return (clean_exit(pss));
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
