/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 08:20:26 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/29 18:36:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "21sh.h"
#include "libft.h"

int	rule_create_cmd(t_parser *parser, t_ast_token *list)
{
	t_command	*new_command;
	t_ast		*new_node;

	(void)parser;
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

int	rule_add_to_cmd(t_parser *parser, t_ast_token *list)
{
	int			ret;
	t_ast_token	*tmp;

	(void)parser;
	ret = add_to_command(((t_ast *)list->data)->data, list->next->data);
	tmp = list->next->next;
	free(list->next);
	list->next = tmp;
	return (ret);
}

int	rule_create_end(t_parser *parser, t_ast_token *list)
{
	t_ast		*node_end;
	t_ast_token	*tmp;

	(void)parser;
	if (!(node_end = alloc_ast(list->next->data, TT_END, exec_end, free_end)))
		return (1);
	node_end->left = list->data;
	node_end->right = list->next->next->data;
	tmp = list->next->next->next;
	free(list->next->next);
	free(list->next);
	list->next = tmp;
	list->data = node_end;
	return (0);
}
