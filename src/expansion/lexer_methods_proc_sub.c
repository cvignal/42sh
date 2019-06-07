/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_proc_sub.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 19:45:48 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/02 20:03:41 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"

int	exp_lexer_set_proc_sub(struct s_shell *shell, char c, int mask)
{
	if (!(mask & EXP_LEXER_MASK_PROC_SUB))
		return (exp_lexer_dollar_fail(shell, c, mask));
	free(exp_ss_pop(&shell->exp_lexer));
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_PROC_SUB))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_pop_proc_sub(struct s_shell *shell, char c, int mask)
{
	(void)c;
	(void)mask;
	free(exp_ss_pop(&shell->exp_lexer));
	return (EXP_LEXER_RET_CONT);
}
