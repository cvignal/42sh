/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:55:15 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/22 10:18:42 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"
#include "ast.h"

static int		clean_exit(t_lexer *lexer, t_token *list, t_token *current, const char *msg)
{
	t_token	*tmp;

	ft_dprintf(2, "minishell: %s\n", msg);
	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp != current)
		{
			free(tmp->data);
			free(tmp);
		}
	}
	if (current)
	{
		free(current->data);
		free(current);
	}
	while (lexer->lss->state != LSTATE_NONE)
		lss_pop(lexer);
	return (1);
}

static int		handle_ret(t_lexer *lexer, int ret, t_token **current,
		t_token **output)
{
	if (ret & (1 << LEXER_RET_ERROR))
		return (clean_exit(lexer, *output, *current, "syntax error"));
	else if (ret & (1 << LEXER_RET_CREATE))
	{
		if (!(*current = alloc_token()))
			return (clean_exit(lexer, *output, *current,
						"unable to allocate memory"));
	}
	else if (ret & (1 << LEXER_RET_CUT))
	{
		set_token_type(*current);
		add_to_token_list(output, *current);
		*current = NULL;
	}
	return (0);
}

static t_token	*get_return(t_lexer *lexer, t_token **output, t_token *current)
{
	t_token		*over;

	if (!lexer->lss || lexer->lss->state != LSTATE_NONE)
	{
		clean_exit(lexer, *output, current, "syntax error");
		return (NULL);
	}
	if (!(over = alloc_token()))
		return (NULL);
	over->type = TT_OVER;
	add_to_token_list(output, over);
	return (*output);
}

t_token			*lex(t_shell *shell, const char *line)
{
	t_token	*output;
	t_token	*current;
	int		pos;
	int		ret;

	output = NULL;
	current = NULL;
	pos = 0;
	ret = 0;
	while (!(ret & (1 << LEXER_RET_OVER)))
	{
		if (line[pos] >= 0)
		{
			ret = shell->lexer.lexer_actions[shell->lexer.lss->state]
				[(int)line[pos]](shell, current, line[pos]);
			if (handle_ret(&shell->lexer, ret, &current, &output))
				return (NULL);
			pos += !!(ret & (1 << LEXER_RET_CONT));
		}
		else
			return (clean_exit(&shell->lexer, output, current,
						"syntax error") == 1 ? NULL : NULL);
	}
	return (get_return(&shell->lexer, &output, current));
}
