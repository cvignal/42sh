/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:30:21 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/30 00:53:40 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "expand.h"
#include "libft.h"

static int	clean_exit(t_exp_lexer *lexer)
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
	if (lexer->ret.data)
		ft_deltab(&lexer->ret.data);
	return (1);
}

static void	reset_exp_lexer(t_shell *shell, int mask)
{
	const char	*ifs;

	if (mask & EXP_LEXER_MASK_FIELD_SPLITTING)
		shell->exp_lexer.split = 1;
	else
		shell->exp_lexer.split = 0;
	ft_bzero(&shell->exp_lexer.ret, sizeof(shell->exp_lexer.ret));
	ft_bzero(&shell->exp_lexer.state->buffer,
			sizeof(shell->exp_lexer.state->buffer));
	ifs = get_var_value(get_var(shell->vars, "IFS"));
	if (!ifs)
		ifs = DEFAULT_IFS;
	shell->exp_lexer.ifs = ifs;
}

static int		expand(t_shell *shell, char *arg, int mask)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	reset_exp_lexer(shell, mask);
	while (!(ret & EXP_LEXER_RET_OVER))
	{
		ret = shell->exp_lexer.methods[shell->exp_lexer.state->state]
			[(int)arg[i]](shell, arg[i], mask);
		if (ret & EXP_LEXER_RET_ERROR)
			return (clean_exit(&shell->exp_lexer));
		if (ret & EXP_LEXER_RET_CONT)
			++i;
	}
	if (shell->exp_lexer.state->state != EXP_STATE_WORD)
		return (clean_exit(&shell->exp_lexer));
	if (shell->exp_lexer.state->buffer.buffer)
	{
		ft_arrayadd(&shell->exp_lexer.ret, shell->exp_lexer.state->buffer.buffer);
		free(shell->exp_lexer.state->buffer.buffer);
	}
	return (0);
}

char		*expand_no_split(struct s_shell *shell, char *arg,
		int *error, int mask)
{
	char	*res;

	*error = 0;
	if (expand(shell, arg, mask & ~(EXP_LEXER_MASK_FIELD_SPLITTING)))
	{
		*error = 1;
		return (NULL);
	}
	if (shell->exp_lexer.ret.data)
	{
		res = shell->exp_lexer.ret.data[0];
		free(shell->exp_lexer.ret.data);
	}
	return (res);
}

int			expand_params(t_shell *shell, t_command *command, int mask)
{
	int		i;
	t_array	result;

	ft_bzero(&result, sizeof(result));
	if (command->args_value)
	{
		i = 0;
		while (command->args_value[i])
			free(command->args_value[i++]);
		free(command->args_value);
	}
	i = 0;
	while (command->args[i])
	{
		if (expand(shell, command->args[i], mask))
		{
			ft_deltab(&result.data);
			return (1);
		}
		ft_arraymerge(&result, &shell->exp_lexer.ret);
		free(shell->exp_lexer.ret.data);
		i++;
	}
	command->args_value = result.data;
	return (0);
}

int			expand_redirs(t_shell *shell, t_redir *list, int mask)
{
	t_redir	*curr;

	curr = list;
	while (curr)
	{
		if (curr->target_value)
			free(curr->target_value);
		if (curr->target)
		{
			if (expand(shell, curr->target, mask))
				return (1);
			curr->target_value = shell->exp_lexer.state->buffer.buffer;
		}
		else
			curr->target_value = NULL;
		curr = curr->next;
	}
	return (0);
}
