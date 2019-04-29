/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 21:12:58 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/29 16:22:42 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"

int	exp_lexer_push_squote(struct s_shell *shell, char c, int mask)
{
	if (!(mask & EXP_LEXER_MASK_QUOTE))
		return (exp_lexer_add_to_buff(shell, c, mask));
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_SQUOTE))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_push_dquote(struct s_shell *shell, char c, int mask)
{
	if (!(mask & EXP_LEXER_MASK_QUOTE))
		return (exp_lexer_add_to_buff(shell, c, mask));
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_DQUOTE))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_pop_quote(struct s_shell *shell, char c, int mask)
{
	char	*value;

	(void)c;
	(void)mask;
	value = exp_ss_pop(&shell->exp_lexer);
	if (value)
	{
		if (add_string_to_exp_buff(&shell->exp_lexer, value))
		{
			free(value);
			return (EXP_LEXER_RET_ERROR);
		}
		free(value);
	}
	return (EXP_LEXER_RET_CONT);
}
