/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 22:24:25 by gchainet          #+#    #+#             */
/*   Updated: 2019/07/10 04:44:28 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"

int	exp_lexer_push_dollar(t_shell *shell, char c, int mask)
{
	(void)c;
	(void)mask;
	if (!(mask & EXP_LEXER_MASK_VARIABLE))
		return (exp_lexer_add_to_buff(shell, c, mask));
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_DOLLAR))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_set_var(t_shell *shell, char c, int mask)
{
	(void)c;
	(void)mask;
	free(exp_ss_pop(&shell->exp_lexer));
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_VAR))
		return (EXP_LEXER_RET_ERROR);
	return (0);
}

int	exp_lexer_dollar_fail(t_shell *shell, char c, int mask)
{
	(void)mask;
	(void)c;
	free(exp_ss_pop(&shell->exp_lexer));
	if (add_char_to_exp_buff(&shell->exp_lexer, '$'))
		return (EXP_LEXER_RET_ERROR);
	return (0);
}
