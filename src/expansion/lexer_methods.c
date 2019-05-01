/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 20:59:58 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/01 22:38:55 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include "libft.h"

int	exp_lexer_add_to_buff(t_shell *shell, char c, int mask)
{
	(void)mask;
	if (add_char_to_exp_buff(&shell->exp_lexer, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_pop_add_to_buff(t_shell *shell, char c, int mask)
{
	char	*tmp;

	(void)mask;
	if (add_char_to_exp_buff(&shell->exp_lexer, c))
		return (EXP_LEXER_RET_ERROR);
	tmp = exp_ss_pop(&shell->exp_lexer);
	if (add_string_to_exp_buff(&shell->exp_lexer, tmp))
	{
		free(tmp);
		return (EXP_LEXER_RET_ERROR);
	}
	free(tmp);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_add_to_var(t_shell *shell, char c, int mask)
{
	if (is_special_var(c))
	{
		if (shell->exp_lexer.state->buffer.pos == 0)
		{
			if (add_char_to_exp_buff(&shell->exp_lexer, c))
				return (EXP_LEXER_RET_ERROR);
		}
		if (exp_lexer_cut_var(shell, c, mask) == EXP_LEXER_RET_ERROR)
			return (EXP_LEXER_RET_ERROR);
		return (EXP_LEXER_RET_CONT);
	}
	if (add_char_to_exp_buff(&shell->exp_lexer, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_cut_var(t_shell *shell, char c, int mask)
{
	const char	*value;
	char		*name;

	(void)c;
	(void)mask;
	name = exp_ss_pop(&shell->exp_lexer);
	if (shell->exp_lexer.state->state == EXP_STATE_WORD)
		shell->exp_lexer.split = 1;
	if (name)
	{
		if ((value = get_var_value(get_var(shell->vars , name))))
		{
			if (add_string_to_exp_buff(&shell->exp_lexer, value))
			{
				free(name);
				return (EXP_LEXER_RET_ERROR);
			}
		}
		free(name);
	}
	if (shell->exp_lexer.state->state == EXP_STATE_WORD)
		shell->exp_lexer.split = 0;
	return (0);
}

int	exp_lexer_push_var(t_shell *shell, char c, int mask)
{
	if (!(mask & EXP_LEXER_MASK_VARIABLE))
		return (exp_lexer_add_to_buff(shell, c, mask));
	shell->exp_lexer.split = 1;
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_VAR))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}
