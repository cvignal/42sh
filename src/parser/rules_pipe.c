/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:14:32 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 18:48:34 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "21sh.h"
#include "parser.h"

int	rule_create_pipeline(t_ast_token *list)
{
	t_pipeline	*pipeline;

	if (!(pipeline = create_pipeline(((t_ast *)list->data)->data)))
		return (1);
	list->type = TT_PIPELINE;
	((t_ast *)list->data)->data = pipeline;
	((t_ast *)list->data)->del = &free_pipeline;
	((t_ast *)list->data)->exec = &exec_pipeline;
	return (0);
}

int	rule_add_to_pipeline(t_ast_token *list)
{
	t_pipeline	*iter;
	t_pipeline	*new_pipeline;
	t_ast_token	*tmp;

	new_pipeline = ((t_ast *)list->next->next->data)->data;
	iter = ((t_ast *)list->data)->data;
	while (iter->next)
		iter = iter->next;
	iter->next = new_pipeline;
	tmp = list->next->next->next;
	free(list->next->next->data);
	free(list->next->next);
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	return (0);
}
