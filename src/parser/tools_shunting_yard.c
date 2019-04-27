/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_shunting_yard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:00:41 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/27 18:55:18 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ast.h"
#include "parser.h"
#include "libft.h"

int				set_leaves(t_ast *node, t_token **stack)
{
	t_token			*right;
	t_token			*left;
	const t_op_prop	*prop;

	if (!node)
		return (1);
	if (!(right = pop_ast_token(stack)))
		return (1);
	node->right = right->data;
	free(right);
	node->left = NULL;
	if (!(prop = get_op_prop(node->type)))
		return (1);
	if (prop->arity == 1)
		return (0);
	if (!(left = pop_ast_token(stack)))
	{
		node->right->del(node->right);
		node->right = NULL;
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
