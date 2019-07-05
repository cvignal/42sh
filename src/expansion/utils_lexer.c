/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:25:36 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/05 14:00:24 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "shell.h"

static int	clean_lx(t_shell *shell)
{
	free(shell->exp_lexer.state->buffer.buffer);
	return (1);
}

int			expand_main(t_shell *shell, char *arg, int mask)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	reset_exp_lexer(shell);
	while (!(ret & EXP_LEXER_RET_OVER))
	{
		ret = shell->exp_lexer.methods[shell->exp_lexer.state->state]
			[(int)arg[i]](shell, arg[i], mask);
		if (ret & EXP_LEXER_RET_ERROR)
			return (clean_exit_exp_lexer(&shell->exp_lexer));
		if (ret & EXP_LEXER_RET_CONT)
			++i;
	}
	if (shell->exp_lexer.state->buffer.buffer)
	{
		if (ft_arrayadd(&shell->exp_lexer.ret
					, shell->exp_lexer.state->buffer.buffer))
			return (clean_lx(shell));
		free(shell->exp_lexer.state->buffer.buffer);
	}
	return (0);
}

int			expand_redirs(t_shell *shell, t_redir *list, int mask)
{
	t_redir	*curr;
	int		error;

	curr = list;
	error = 0;
	while (curr)
	{
		if (curr->target_value)
			free(curr->target_value);
		if (curr->target)
		{
			curr->target_value = expand_no_split(shell, curr->target,
					&error, mask);
			if (error)
				return (1);
		}
		else
			curr->target_value = NULL;
		curr = curr->next;
	}
	return (0);
}

char		*expand_no_split(struct s_shell *shell, char *arg,
		int *error, int mask)
{
	char	*res;

	*error = 0;
	res = NULL;
	if (expand_main(shell, arg, mask & ~(EXP_LEXER_MASK_FIELD_SPLITTING)))
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
