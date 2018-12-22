/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_meta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 10:50:50 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/22 17:13:14 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "ast.h"

int	lexer_add_meta(t_shell *shell, t_token *token, char c)
{
	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	if (get_token_type(token) == TT_WORD)
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
	t_ttype	type;

	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	if ((type = get_token_type(token) != TT_WORD))
	{
		shell->lexer.lss->state = LSTATE_META;
		token->type = type;
		return (1 << LEXER_RET_CONT);
	}
	token->data[--token->len] = 0;
	lss_pop(&shell->lexer);
	return (1 << LEXER_RET_CUT);
}
