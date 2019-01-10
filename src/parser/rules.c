/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 08:20:26 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/09 10:41:05 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "shell.h"
#include "libft.h"

int	rule_create_cmd(t_parser *parser, t_ast_token *list)
{
	t_command	*new_command;
	t_ast		*new_node;
	int			type;

	(void)parser;
	type = keyword_type(list->data);
	if (type == TT_WORD)
	{
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
	}
	else
		list->type = type;
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

	(void)parser;
	if (!(node_end = alloc_ast(NULL, TT_END, exec_end, free_end)))
		return (1);
	free(list->data);
	list->data = node_end;
	list->type = TT_OP;
	return (0);
}

int	rule_create_end_second(t_parser *parser, t_ast_token *list)
{
	t_ast	*node_end;

	(void)parser;
	node_end = alloc_ast(NULL, TT_END, exec_end, free_end);
	if (!node_end)
		return (1);
	free(list->next->data);
	list->next->data = node_end;
	list->next->type = TT_OP;
	return (0);
}
