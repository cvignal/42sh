/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 21:12:58 by gchainet          #+#    #+#             */
/*   Updated: 2019/03/29 18:13:27 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"

int	exp_lexer_push_squote(struct s_shell *shell, t_exp_lexer *lexer, char c)
{
	(void)shell;
	(void)c;
	if (add_to_exp_buff(&lexer->buffer, 0))
		return (EXP_LEXER_RET_ERROR);
	--lexer->buffer.pos;
	if (exp_ss_push(lexer, EXP_STATE_SQUOTE))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_push_dquote(struct s_shell *shell, t_exp_lexer *lexer, char c)
{
	(void)shell;
	(void)c;
	if (add_to_exp_buff(&lexer->buffer, 0))
		return (EXP_LEXER_RET_ERROR);
	--lexer->buffer.pos;
	if (exp_ss_push(lexer, EXP_STATE_DQUOTE))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_pop_quote(struct s_shell *shell, t_exp_lexer *lexer, char c)
{
	(void)shell;
	(void)c;
	exp_ss_pop(lexer);
	return (EXP_LEXER_RET_CONT);
}
