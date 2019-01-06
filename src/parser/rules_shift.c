/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:10:50 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 10:32:22 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "21sh.h"
#include "libft.h"

int	rule_shift_first(t_parser *parser, t_ast_token *list)
{
	t_ast_token	*tmp;

	(void)list;
	tmp = parser->input_queue->next;
	free(parser->input_queue);
	parser->input_queue = tmp;
	return (0);
}

int	rule_shift_second(t_parser *parser, t_ast_token *list)
{
	t_ast_token	*tmp;

	(void)parser;
	tmp = list->next->next;
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	return (0);
}
