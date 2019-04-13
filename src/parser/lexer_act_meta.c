/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_meta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 10:50:50 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/13 05:10:15 by gchainet         ###   ########.fr       */
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
	if (type == TT_ARI)
	{
		lss_pop(&shell->lexer);
		token->type = TT_ARI;
		if (lss_push(&shell->lexer, LSTATE_ARI_FIRST_PASS))
			return (1 << LEXER_RET_ERROR);
	}
	else if (type == TT_WORD)
	{
		token->len--;
		token->data[token->len] = 0;
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
	token->data[--token->len] = 0;
	lss_pop(&shell->lexer);
	return (1 << LEXER_RET_CUT);
}
