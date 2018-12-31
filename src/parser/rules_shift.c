/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:10:50 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/29 18:40:24 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "21sh.h"
#include "libft.h"

int	rule_shift_first(t_parser *parser, t_ast_token *list)
{
	t_ast_token	*tmp;

	(void)parser;
	free(list->data);
	list->data = list->next->data;
	list->type = list->next->type;
	tmp = list->next;
	list->next = list->next->next;
	free(tmp);
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
