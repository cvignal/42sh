/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_special_params.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marin </var/spool/mail/marin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:57:18 by marin             #+#    #+#             */
/*   Updated: 2019/06/02 18:19:58 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"

int	exp_lexer_set_special_param(struct s_shell *shell, char c, int mask)
{
	(void)c;
	(void)mask;
	free(exp_ss_pop(&shell->exp_lexer));
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_SPECIAL_PARAM))
		return (EXP_LEXER_RET_ERROR);
	if (add_char_to_exp_buff(&shell->exp_lexer, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_cut_special_param(struct s_shell *shell, char c, int mask)
{
	(void)c;
	(void)mask;
	char	*name;

	name = exp_ss_pop(&shell->exp_lexer);
	if (shell->exp_lexer.state->state == EXP_STATE_WORD
			&& (mask & EXP_LEXER_MASK_FIELD_SPLITTING))
		shell->exp_lexer.split = 1;
	if (expand_special_params(&shell->exp_lexer, shell, name[0]))
			return (EXP_LEXER_RET_ERROR);
	if (shell->exp_lexer.state->state == EXP_STATE_WORD)
		shell->exp_lexer.split = 0;
	return (0);
}
