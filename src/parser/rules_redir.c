/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 11:32:11 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/21 10:52:36 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "parser.h"
#include "minishell.h"

static int	rule_redir_generic(t_ast_token *list, t_ttype type,
		t_redir_act act)
{
	t_command	*command;
	t_ast_token	*tmp;

	command = ((t_ast *)list->data)->data;
	if (add_redir(command, type, list->next->next->data, act))
		return (1);
	tmp = list->next->next->next;
	free(list->next->next->data);
	free(list->next->next);
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	return (0);
}

int	rule_redir_l(t_ast_token *list)
{
	return (rule_redir_generic(list, TT_REDIR_L, &redir_l));
}

int	rule_redir_ll(t_ast_token *list)
{
	return (rule_redir_generic(list, TT_REDIR_LL, &redir_ll));
}

int	rule_redir_r(t_ast_token *list)
{
	return (rule_redir_generic(list, TT_REDIR_R, &redir_r));
}

int	rule_redir_rr(t_ast_token *list)
{
	return (rule_redir_generic(list, TT_REDIR_RR, &redir_rr));
}
