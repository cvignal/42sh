/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 08:20:26 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/20 11:08:18 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "minishell.h"
#include "libft.h"

int	rule_create_cmd(t_ast_token *list)
{
	t_command	*new_command;
	t_ast		*new_node;

	if (!(new_command = alloc_command()))
		return (1);
	add_to_command(new_command, list->data);
	if (!(new_node = alloc_ast(new_command, TT_CMD, exec_cmd, free_cmd)))
	{
		free(new_command);
		return (1);
	}
	list->type = TT_CMD;
	list->data = new_node;
	return (0);
}

int	rule_add_to_cmd(t_ast_token *list)
{
	int			ret;
	t_ast_token	*tmp;

	ret = add_to_command(((t_ast *)list->data)->data, list->next->data);
	tmp = list->next->next;
	free(list->next);
	list->next = tmp;
	return (ret);
}

int	rule_create_end(t_ast_token *list)
{
	t_ast		*node_end;
	t_ast_token	*tmp;

	if (!(node_end = alloc_ast(list->next->data, TT_END, exec_end, free_end)))
		return (1);
	node_end->left = list->data;
	node_end->right = list->next->next->data;
	tmp = list->next->next->next;
	free(list->next->next);
	free(list->next);
	list->next = tmp;
	list->type = TT_CMD;
	list->data = node_end;
	return (0);
}
