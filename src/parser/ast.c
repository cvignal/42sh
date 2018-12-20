/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 08:26:16 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/15 09:55:35 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"

t_ast	*alloc_ast(void *data, t_ttype type, t_exec exec, t_free del)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->type = type;
	new_node->exec = exec;
	new_node->del = del;
	new_node->right = NULL;
	new_node->left = NULL;
	return (new_node);
}

void	free_ast(t_ast *ast)
{
	if (ast)
	{
		ast->del(ast->data);
		free_ast(ast->right);
		free_ast(ast->left);
	}
}
