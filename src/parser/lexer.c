/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:55:15 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/18 22:08:52 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"
#include "ast.h"

static int		clean_exit(t_token *list, t_token *current, const char *msg)
{
	t_token	*tmp;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
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
	return (1);
}

static int		handle_ret(int ret, t_token **current, t_token **output)
{
	if (ret & (1 << LEXER_RET_ERROR))
		return (clean_exit(*output, *current, "syntax error"));
	else if (ret & (1 << LEXER_RET_CREATE))
	{
		if (!(*current = alloc_token()))
			return (clean_exit(*output, *current, "unable to allocate memory"));
	}
	else if (ret & (1 << LEXER_RET_CUT))
	{
		set_token_type(*current);
		add_to_token_list(output, *current);
		*current = NULL;
	}
	return (0);
}

static t_token	*get_return(t_token **output, t_token *current)
{
	t_token		*over;

	if (current)
		add_to_token_list(output, current);
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
	shell->lexer.state = LSTATE_NONE;
	while (line[pos])
	{
		if (line[pos] > 0)
		{
			ret = shell->lexer.lexer_actions[shell->lexer.state]
				[(int)line[pos]](&shell->lexer, current, line[pos]);
			if (handle_ret(ret, &current, &output))
				return (NULL);
			pos += !!(ret & (1 << LEXER_RET_CONT));
		}
		else
			return (clean_exit(output, current, "syntax error") == 1
					? NULL : NULL);
	}
	return (get_return(&output, current));
}
