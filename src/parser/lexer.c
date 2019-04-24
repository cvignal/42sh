/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:55:15 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 09:49:14 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "libft.h"
#include "ast.h"
#include "libft.h"
#include "arithmetic.h"

int				clean_exit_lexer(t_lexer *lexer, t_token **list
		, t_token **current, const char *msg)
{
	t_token	*tmp;

	if (msg)
		ft_dprintf(2, "%s: %s\n", EXEC_NAME, msg);
	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		if (tmp != *current)
		{
			free(tmp->data);
			free(tmp);
		}
	}
	if (current && *current)
	{
		free((*current)->data);
		free(*current);
		*current = NULL;
	}
	while (lexer->lss->state != LSTATE_NONE)
		lss_pop(lexer);
	return (1);
}

static int		handle_ret(t_lexer *lexer, int ret, t_token **current,
		t_token **output)
{
	if (ret & (1 << LEXER_RET_ERROR))
		return (clean_exit_lexer(lexer, output, current, SYNTAX_ERROR_MSG));
	if (ret & (1 << LEXER_RET_CREATE))
	{
		if (!(*current = alloc_token()))
			return (clean_exit_lexer(lexer, output, current, MEMORY_ERROR_MSG));
		(*current)->type = TT_WORD;
	}
	if (ret & (1 << LEXER_RET_CUT))
	{
		(*current)->type = get_token_type(*current, lexer->lss->state);
		add_to_token_list(output, *current);
		*current = NULL;
	}
	if (ret & (1 << LEXER_RET_MORE_INPUT))
		return (1);
	return (0);
}

static t_token	*get_return(t_token **output)
{
	t_token		*over;
	t_token		*ret;

	if (!(over = alloc_token()))
		return (NULL);
	over->type = TT_OVER;
	add_to_token_list(output, over);
	ret = *output;
	*output = NULL;
	return (ret);
}

t_token			*lex(t_shell *shell, const char *input)
{
	int				pos;
	int				ret;

	ret = 0;
	pos = 0;
	while (!(ret & (1 << LEXER_RET_OVER)))
	{
		if (input[pos] >= 0)
		{
			ret = shell->lexer.lexer_actions[shell->lexer.lss->state]
				[(int)input[pos]](shell, shell->current, input[pos]);
			if (handle_ret(&shell->lexer, ret, &shell->current, &shell->output))
				return (NULL);
			pos += !!(ret & (1 << LEXER_RET_CONT));
		}
		else
		{
			clean_exit_lexer(&shell->lexer, &shell->output, &shell->current
					, SYNTAX_ERROR_MSG);
			return (NULL);
		}
	}
	return (get_return(&shell->output));
}
