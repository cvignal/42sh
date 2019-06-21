/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_curly_exp.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marin </var/spool/mail/marin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 21:52:26 by marin             #+#    #+#             */
/*   Updated: 2019/06/05 23:13:57 by marin            ###   ########.fr       */
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

//TODO: remove
int	exp_lexer_curly_expansion_stop(struct s_shell *shell, char c, int mask)
{
	return (exp_lexer_cut_var(shell, c, mask));
}
