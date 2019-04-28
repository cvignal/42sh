/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_ari.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 22:34:36 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/28 16:29:23 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include "arithmetic.h"

static int	copy_ari_result(t_shell *shell, char *res, char c, int mask)
{
	int	i;

	(void)c;
	(void)mask;
	i = 0;
	while (res[i])
	{
		if (add_to_exp_buff(&shell->exp_lexer.buffer, res[i]))
			return (1);
		++i;
	}
	return (0);
}

int			exp_lexer_set_ari(t_shell *shell, char c, int mask)
{
	if (!(mask & EXP_LEXER_MASK_ARI))
		return (exp_lexer_dollar_fail(shell, c, mask));
	exp_ss_pop(&shell->exp_lexer);
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_ARI))
		return (EXP_LEXER_RET_ERROR);
	return (0);
}

int			exp_lexer_push_ari_paren(t_shell *shell, char c, int mask)
{
	(void)mask;
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_ARI_PAREN))
		return (EXP_LEXER_RET_ERROR);
	if (add_to_exp_buff(&shell->exp_lexer.var, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int			exp_lexer_pop_ari_paren(t_shell *shell, char c, int mask)
{
	(void)mask;
	exp_ss_pop(&shell->exp_lexer);
	if (add_to_exp_buff(&shell->exp_lexer.var, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int			exp_lexer_pop_ari(t_shell *shell, char c, int mask)
{
	t_token	*tokens;
	int		ret;

	exp_ss_pop(&shell->exp_lexer);
	if (lss_push(&shell->lexer, LSTATE_ARI_NONE))
		return (EXP_LEXER_RET_ERROR);
	if (!(tokens = lex(shell, shell->exp_lexer.var.buffer)))
		return (EXP_LEXER_RET_ERROR);
	ft_bzero(&shell->exp_lexer.var, sizeof(shell->exp_lexer.var));
	set_unary(tokens);
	lss_pop(&shell->lexer);
	if (pss_push(&shell->parser, PS_ARI))
		return (EXP_LEXER_RET_ERROR);
	if ((ret = parse(shell, tokens)) == PARSER_COMPLETE)
	{
		shell->parser.ret->exec(shell, shell->parser.ret);
		copy_ari_result(shell, shell->parser.ret->data, c, mask);
		shell->parser.ret->del(shell->parser.ret);
	}
	else if (ret == PARSER_EMPTY)
		copy_ari_result(shell, "0", c, mask);
	else
		return (EXP_LEXER_RET_ERROR);
	return (0);
}
