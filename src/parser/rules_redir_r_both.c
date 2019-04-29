/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir_r_both.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 10:48:50 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/11 22:27:37 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "shell.h"
#include "parser.h"

int	rule_redir_r_both(t_parser *parser, t_token *list)
{
	t_ast		*instr;
	t_redir		*redir;

	instr = parser->pss->ret;
	redir = create_redir(TT_REDIR_R_BOTH, list->next->data,
			&redir_r_both);
	if (!redir)
		return (1);
	add_to_redir_list(instr, redir);
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	return (0);
}
