/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 11:32:11 by gchainet          #+#    #+#             */
/*   Updated: 2019/03/09 14:50:02 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "parser.h"
#include "shell.h"

int			rule_redir_l(t_parser *parser, t_token *list)
{
	t_redir		*redir;

	if (!(redir = create_redir(TT_REDIR_L, list->next->data,
					&redir_l)))
		return (1);
	if (ft_isdigit(*(char *)list->data))
	{
		redir->in = ft_atoi(list->data);
		if (redir->in < 0 || redir->in > 9)
		{
			free(redir);
			return (1);
		}
	}
	else
		redir->in = STDIN_FILENO;
	add_to_redir_list(parser->pss->ret, redir);
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	return (0);
}

int			rule_redir_ll(t_parser *parser, t_token *list)
{
	t_redir		*redir;

	if (!(redir = create_redir(TT_REDIR_LL, list->next->data,
					&redir_ll)))
		return (1);
	if (ft_isdigit(*(char *)list->data))
	{
		redir->in = ft_atoi(list->data);
		if (redir->in < 0 || redir->in > 9)
		{
			free(redir);
			return (1);
		}
	}
	else
		redir->in = STDIN_FILENO;
	add_to_redir_list(parser->pss->ret, redir);
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	return (0);
}

int			rule_redir_r(t_parser *parser, t_token *list)
{
	t_redir		*redir;

	if (!(redir = create_redir(TT_REDIR_R, list->next->data,
					&redir_r)))
		return (1);
	if (ft_isdigit(*(char *)list->data))
	{
		redir->in = ft_atoi(list->data);
		if (redir->in < 0 || redir->in > 9)
		{
			free(redir->target);
			free(redir);
			return (1);
		}
	}
	else
		redir->in = STDOUT_FILENO;
	add_to_redir_list(parser->pss->ret, redir);
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	return (0);
}

int			rule_redir_rr(t_parser *parser, t_token *list)
{
	t_redir		*redir;

	if (!(redir = create_redir(TT_REDIR_RR, list->next->data,
					&redir_rr)))
		return (1);
	if (ft_isdigit(*(char *)list->data))
	{
		redir->in = ft_atoi(list->data);
		if (redir->in < 0 || redir->in > 9)
		{
			free(redir);
			return (1);
		}
	}
	else
		redir->in = STDOUT_FILENO;
	add_to_redir_list(parser->pss->ret, redir);
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	free(parser->input_queue->data);
	free(pop_ast_token(&parser->input_queue));
	return (0);
}
