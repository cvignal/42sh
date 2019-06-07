/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir_close.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:45:06 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/02 23:50:16 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ast.h"
#include "shell.h"

static t_redir	*create_redir_close(char *data, int default_fd, t_ttype type)
{
	t_redir		*new_redir;

	new_redir = malloc(sizeof(*new_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->next = NULL;
	new_redir->redir_act = &redir_close;
	new_redir->target = NULL;
	new_redir->target_value = NULL;
	new_redir->applied = 0;
	new_redir->fd = -1;
	if (ft_isdigit(*data))
	{
		new_redir->in = ft_atoi(data);
		if (new_redir->in < 0 || new_redir->in > 9)
		{
			free(new_redir);
			return (NULL);
		}
	}
	else
		new_redir->in = default_fd;
	return (new_redir);
}

int				rule_redir_close_generic(t_parser *parser, t_token *list,
		int default_fd, t_ttype type)
{
	t_ast		*instr;
	t_redir		*redir;
	t_redir		*iter;

	if (!(redir = create_redir_close(list->data, default_fd, type)))
		return (1);
	instr = parser->pss->ret;
	iter = instr->redir_list;
	if (!iter)
		instr->redir_list = redir;
	else
	{
		while (iter->next)
			iter = iter->next;
		iter->next = redir;
	}
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	return (0);
}

int				rule_redir_r_close(t_parser *parser, t_token *list)
{
	return (rule_redir_close_generic(parser
				, list, STDOUT_FILENO, TT_REDIR_R_CLOSE));
}

int				rule_redir_l_close(t_parser *parser, t_token *list)
{
	return (rule_redir_close_generic(parser
				, list, STDIN_FILENO, TT_REDIR_L_CLOSE));
}
