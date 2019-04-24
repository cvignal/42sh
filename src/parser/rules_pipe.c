/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:14:32 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/29 14:51:48 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "shell.h"
#include "parser.h"

int	rule_pipe(t_parser *parser, t_token *list)
{
	t_ast		*pipe_node;

	(void)parser;
	pipe_node = alloc_ast(NULL, TT_PIPE, &exec_pipeline, &free_pipeline);
	if (!pipe_node)
		return (1);
	free(list->data);
	list->data = pipe_node;
	list->type = TT_OP;
	return (0);
}
