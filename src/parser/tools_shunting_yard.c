/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_shunting_yard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:00:41 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/24 17:28:18 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ast.h"
#include "parser.h"
#include "libft.h"

int				set_leaves(t_ast *node, t_ast_token **stack)
{
	t_ast_token	*right;
	t_ast_token	*left;

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

t_ast			*end_queue_to_ast(t_pss *pss)
{
	t_ast	*ret;

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
