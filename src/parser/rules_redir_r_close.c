/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir_r_close.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 19:38:21 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 07:23:40 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "21sh.h"

static t_redir	*create_redir_close(char *data)
{
	t_redir		*new_redir;

	new_redir = malloc(sizeof(*new_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = TT_REDIR_R_CLOSE;
	new_redir->next = NULL;
	new_redir->redir_act = &redir_r_close;
	new_redir->target = NULL;
	if (ft_isdigit(*data))
		new_redir->in = ft_atoi(data);
	else
		new_redir->in = 1;
	return (new_redir);
}

int				rule_redir_r_close(t_parser *parser, t_ast_token *list)
{
	t_ast		*instr;
	t_ast_token	*tmp;
	t_redir		*redir;
	t_redir		*iter;

	(void)parser;
	redir = create_redir_close(list->next->data);
	instr = list->data;
	iter = instr->redir_list;
	if (!iter)
		instr->redir_list = redir;
	else
	{
		while (iter->next)
			iter = iter->next;
		iter->next = redir;
	}
	tmp = list->next->next;
	free(list->next->data);
	free(list->next);
	list->next = tmp;
	return (0);
}
