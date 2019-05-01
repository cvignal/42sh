/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_ari.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 22:34:36 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/01 23:26:51 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include "arithmetic.h"

int			exp_lexer_set_ari(t_shell *shell, char c, int mask)
{
	if (!(mask & EXP_LEXER_MASK_ARI))
		return (exp_lexer_dollar_fail(shell, c, mask));
	free(exp_ss_pop(&shell->exp_lexer));
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_ARI))
		return (EXP_LEXER_RET_ERROR);
	return (0);
}

int			exp_lexer_push_ari_paren(t_shell *shell, char c, int mask)
{
	(void)mask;
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_ARI_PAREN))
		return (EXP_LEXER_RET_ERROR);
	if (add_char_to_exp_buff(&shell->exp_lexer, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int			exp_lexer_pop_ari_paren(t_shell *shell, char c, int mask)
{
	char	*tmp;

	(void)mask;
	tmp = exp_ss_pop(&shell->exp_lexer);
	if (add_string_to_exp_buff(&shell->exp_lexer, tmp))
	{
		free(tmp);
		return (EXP_LEXER_RET_ERROR);
	}
	free(tmp);
	if (add_char_to_exp_buff(&shell->exp_lexer, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

static int	exec_ari(t_shell *shell)
{
	t_ast	*ast;
	int		ret;

	ast = shell->parser.ret;
	ast->exec(shell, ast);
	if (ast->data)
	{
		add_string_to_exp_buff(&shell->exp_lexer, ast->data);
		ret = 0;
	}
	else
		ret = 1;
	ast->del(ast);
	return (ret);
}

static int	parse_and_exec_ari(t_shell *shell, t_token *tokens, int mask)
{
	int		ret;

	if (pss_push(&shell->parser, PS_ARI))
		return (EXP_LEXER_RET_ERROR);
	if (shell->exp_lexer.state->state == EXP_STATE_WORD
			&& (mask & EXP_LEXER_MASK_FIELD_SPLITTING))
		shell->exp_lexer.split = 1;
	if ((ret = parse(shell, tokens)) == PARSER_COMPLETE)
	{
		if (exec_ari(shell))
			return (EXP_LEXER_RET_ERROR);
	}
	else if (ret == PARSER_EMPTY)
		add_string_to_exp_buff(&shell->exp_lexer, "0");
	else
		return (EXP_LEXER_RET_ERROR);
	shell->exp_lexer.split = 0;
	return (0);
}

int			exp_lexer_pop_ari(t_shell *shell, char c, int mask)
{
	t_token	*tokens;
	char	*stmt;

	(void)c;
	if (lss_push(&shell->lexer, LSTATE_ARI_NONE))
		return (EXP_LEXER_RET_ERROR);
	stmt = exp_ss_pop(&shell->exp_lexer);
	if (!(tokens = lex(shell, stmt)))
	{
		free(stmt);
		return (EXP_LEXER_RET_ERROR);
	}
	free(stmt);
	set_unary(tokens);
	lss_pop(&shell->lexer);
	return (parse_and_exec_ari(shell, tokens, mask));
}
