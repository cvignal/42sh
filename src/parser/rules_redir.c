/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 11:32:11 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 07:55:06 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "parser.h"
#include "21sh.h"

static int	rule_redir_generic(t_ast_token *list, t_ttype type, int def_in,
		t_redir_act act)
{
	t_ast		*instr;
	t_ast_token	*tmp;
	t_redir		*redir;

	instr = list->data;
	redir = create_redir(type, list->next->next->data, act);
	if (!redir)
		return (1);
	if (ft_isdigit(*(char *)list->next->data))
		redir->in = ft_atoi(list->next->data);
	else
		redir->in = def_in;
	add_to_redir_list(instr, redir);
	tmp = list->next->next->next;
	free(list->next->next->data);
	free(list->next->next);
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	return (0);
}

int			rule_redir_l(t_parser *parser, t_ast_token *list)
{
	(void)parser;
	return (rule_redir_generic(list, TT_REDIR_L, STDIN_FILENO, &redir_l));
}

int			rule_redir_ll(t_parser *parser, t_ast_token *list)
{
	(void)parser;
	return (rule_redir_generic(list, TT_REDIR_LL, STDIN_FILENO, &redir_ll));
}

int			rule_redir_r(t_parser *parser, t_ast_token *list)
{
	(void)parser;
	return (rule_redir_generic(list, TT_REDIR_R, STDOUT_FILENO, &redir_r));
}

int			rule_redir_rr(t_parser *parser, t_ast_token *list)
{
	(void)parser;
	return (rule_redir_generic(list, TT_REDIR_RR, STDOUT_FILENO, &redir_rr));
}
