/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 08:17:49 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/07 16:47:37 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"

int	lexer_push_squote(t_shell *shell, t_token *token, char c)
{
	(void)token;
	(void)c;
	if (lss_push(&shell->lexer, LSTATE_SQUOTE))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CONT);
}

int	lexer_push_dquote(t_shell *shell, t_token *token, char c)
{
	(void)token;
	(void)c;
	if (lss_push(&shell->lexer, LSTATE_DQUOTE))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CONT);
}
