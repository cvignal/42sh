/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:30:21 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/29 22:19:16 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "expand.h"
#include "libft.h"

static char	*clean_exit(t_exp_lexer *lexer, int *error)
{
	t_exp_ss	*next;

	while (lexer->state && lexer->state->state != EXP_STATE_WORD)
	{
		next = lexer->state->next;
		if (lexer->state->buffer.buffer)
			free(lexer->state->buffer.buffer);
		free(lexer->state);
		lexer->state = next;
	}
	*error = 1;
	return (NULL);
}

static char	*expand(t_shell *shell, char *arg, int *error, int mask)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	ft_bzero(&shell->exp_lexer.state->buffer,
			sizeof(shell->exp_lexer.state->buffer));
	while (!(ret & EXP_LEXER_RET_OVER))
	{
		ret = shell->exp_lexer.methods[shell->exp_lexer.state->state]
			[(int)arg[i]](shell, arg[i], mask);
		if (ret & EXP_LEXER_RET_ERROR)
			return (clean_exit(&shell->exp_lexer, error));
		if (ret & EXP_LEXER_RET_CONT)
			++i;
	}
	if (shell->exp_lexer.state->state != EXP_STATE_WORD)
		return (clean_exit(&shell->exp_lexer, error));
	if (shell->exp_lexer.state->buffer.buffer)
		return (shell->exp_lexer.state->buffer.buffer);
	return (ft_strdup(""));
}

char		*do_expand(t_shell *shell, char *arg, int *error, int mask)
{
	char	*ret;

	ret = expand(shell, arg, error, mask);
	return (ret);
}

int			expand_params(t_shell *shell, t_command *command, int mask)
{
	int		i;
	int		error;

	i = 0;
	error = 0;
	while (command->args[i])
	{
		if (command->args_value[i])
			free(command->args_value[i]);
		command->args_value[i] = do_expand(shell, command->args[i], &error
				, mask);
		if (error)
			return (1);
		i++;
	}
	command->args_value[i] = NULL;
	return (0);
}

int			expand_redirs(t_shell *shell, t_redir *list, int mask)
{
	t_redir	*curr;
	int		error;

	error = 0;
	curr = list;
	while (curr)
	{
		if (curr->target)
			curr->target_value = do_expand(shell, curr->target, &error, mask);
		else
			curr->target_value = NULL;
		if (error)
			return (1);
		curr = curr->next;
	}
	return (0);
}
