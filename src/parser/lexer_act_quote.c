/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 08:17:49 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/22 11:28:30 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

int	lexer_create_dquote(t_shell *shell, t_token *token, char c)
{
	int	ret;

	(void)token;
	(void)c;
	if (lss_push(&shell->lexer, LSTATE_DQUOTE))
		return (1 << LEXER_RET_ERROR);
	ret = (1 << LEXER_RET_CREATE);
	ret |= (1 << LEXER_RET_CONT);
	return (ret);
}

int	lexer_create_squote(t_shell *shell, t_token *token, char c)
{
	int	ret;

	(void)token;
	(void)c;
	if (lss_push(&shell->lexer, LSTATE_SQUOTE))
		return (1 << LEXER_RET_ERROR);
	ret = (1 << LEXER_RET_CREATE);
	ret |= (1 << LEXER_RET_CONT);
	return (ret);
}
