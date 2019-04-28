/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 21:18:39 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/28 05:06:30 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "expand.h"
#include "libft.h"

static char	*clean_exit(t_exp_lexer *lexer, int *error)
{
	if (lexer->buffer.pos)
		free(lexer->buffer.buffer);
	if (lexer->var.pos)
		free(lexer->var.buffer);
	*error = 1;
	return (NULL);
}

static char	*expand(t_shell *shell, char *arg, int *error, int mask)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	ft_bzero(&shell->exp_lexer.buffer, sizeof(shell->exp_lexer.buffer));
	ft_bzero(&shell->exp_lexer.var, sizeof(shell->exp_lexer.var));
	while (!(ret & EXP_LEXER_RET_OVER))
	{
		ret = shell->exp_lexer.methods[shell->exp_lexer.state->state]
			[(int)arg[i]](shell, arg[i], mask);
		if (ret & EXP_LEXER_RET_ERROR)
			return (clean_exit(&shell->exp_lexer, error));
		if (ret & EXP_LEXER_RET_CONT)
			++i;
	}
	if (shell->exp_lexer.buffer.buffer)
		expand_home(shell, error, mask);
	return (shell->exp_lexer.buffer.buffer);
}

char		*do_expand(t_shell *shell, char *arg, int *error, int mask)
{
	char	*tmp;
	char	*ret;

	ret = NULL;
	if (mask & EXP_LEXER_MASK_ARI)
	{
		tmp = expand(shell, arg, error, mask & (~EXP_LEXER_MASK_ARI));
		if (!*error)
		{
			ret = expand(shell, tmp, error, EXP_LEXER_MASK_ARI);
			free(tmp);
		}
	}
	else
		ret = expand(shell, arg, error, mask);
	return (ret);
}

int			expand_params(t_shell *shell, t_command *command, int mask)
{
	int		i;
	int		j;
	int		error;

	i = 0;
	j = 0;
	error = 0;
	while (command->args[i])
	{
		if (command->args_value[i - j])
			free(command->args_value[i - j]);
		command->args_value[i - j] = do_expand(shell, command->args[i], &error
				, mask);
		if (error)
			return (1);
		if (!command->args_value[i - j])
			j++;
		i++;
	}
	command->args_value[i - j] = NULL;
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
