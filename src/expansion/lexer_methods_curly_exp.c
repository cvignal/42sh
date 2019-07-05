/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_curly_exp.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 14:14:39 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/05 14:14:59 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	exp_lexer_curly_expansion_start(struct s_shell *shell, char c, int mask)
{
	(void)c;
	(void)mask;
	free(exp_ss_pop(&shell->exp_lexer));
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_CURLY_EXP))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_set_ari(t_shell *shell, char c, int mask)
{
	if (!(mask & EXP_LEXER_MASK_ARI))
		return (exp_lexer_dollar_fail(shell, c, mask));
	free(exp_ss_pop(&shell->exp_lexer));
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_ARI)
			|| exp_lexer_push_ari_paren(shell, c, mask) & EXP_LEXER_RET_ERROR
			|| exp_lexer_push_ari_paren(shell, c, mask) & EXP_LEXER_RET_ERROR)
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_add_to_buff(t_shell *shell, char c, int mask)
{
	(void)mask;
	if (add_char_to_exp_buff(&shell->exp_lexer, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_curly_expansion_stop(struct s_shell *shell, char c, int mask)
{
	return (exp_lexer_cut_var(shell, c, mask));
}
