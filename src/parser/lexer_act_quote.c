/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 08:17:49 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/08 13:53:45 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"

int	lexer_push_squote(t_shell *shell, t_token *token, char c)
{
	if (lss_push(&shell->lexer, LSTATE_SQUOTE))
		return (1 << LEXER_RET_ERROR);
	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CONT);
}

int	lexer_push_dquote(t_shell *shell, t_token *token, char c)
{
	if (lss_push(&shell->lexer, LSTATE_DQUOTE))
		return (1 << LEXER_RET_ERROR);
	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CONT);
}

int	lexer_pop_quote(t_shell *shell, t_token *token, char c)
{
	lss_pop(&shell->lexer);
	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CONT);
}
