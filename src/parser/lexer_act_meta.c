/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_meta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 10:50:50 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/27 23:56:27 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"
#include "ast.h"

int	lexer_add_meta(t_shell *shell, t_token *token, char c)
{
	int	type;

	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	type = get_token_type(token, shell->lexer.lss->state);
	if (type == TT_WORD)
	{
		token->len--;
		((char *)token->data)[token->len] = 0;
		lss_pop(&shell->lexer);
		return (1 << LEXER_RET_CUT);
	}
	return (1 << LEXER_RET_CONT);
}

int	lexer_create_meta(t_shell *shell, t_token *token, char c)
{
	(void)token;
	(void)c;
	if (lss_push(&shell->lexer, LSTATE_META))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CREATE);
}

int	lexer_push_paren(t_shell *shell, t_token *token, char c)
{
	if (!token->len)
		token->type = TT_PAR;
	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	if (lss_push(&shell->lexer, LSTATE_PAREN))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CONT);
}

int	lexer_pop_paren(t_shell *shell, t_token *token, char c)
{
	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	lss_pop(&shell->lexer);
	if (shell->lexer.lss->state == LSTATE_NONE)
	{
		lss_pop(&shell->lexer);
		return ((1 << LEXER_RET_CUT) | (1 << LEXER_RET_CONT));
	}
	return (1 << LEXER_RET_CONT);
}

int	lexer_try_meta(t_shell *shell, t_token *token, char c)
{
	int	type;

	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	if ((type = get_token_type(token, shell->lexer.lss->state)) != TT_WORD)
	{
		shell->lexer.lss->state = LSTATE_META;
		token->type = type;
		return (1 << LEXER_RET_CONT);
	}
	((char *)token->data)[--token->len] = 0;
	lss_pop(&shell->lexer);
	return (1 << LEXER_RET_CUT);
}
