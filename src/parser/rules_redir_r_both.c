/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir_r_both.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 10:48:50 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/29 18:39:20 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "21sh.h"
#include "parser.h"

int	rule_redir_r_both(t_parser *parser, t_ast_token *list)
{
	t_command	*command;
	t_redir		*redir;
	t_ast_token	*tmp;

	(void)parser;
	command = ((t_ast *)list->data)->data;
	redir = create_redir(TT_REDIR_R_BOTH, list->next->next->data,
			&redir_r_both);
	if (!redir)
		return (1);
	add_to_redir_list(command, redir);
	tmp = list->next->next->next;
	free(list->next->next->data);
	free(list->next->next);
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	return (0);
}
