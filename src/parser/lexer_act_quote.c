/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 08:17:49 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/22 09:05:12 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	lexer_create_dquote(t_lexer *lexer, t_token *token, char c)
{
	int	ret;

	(void)token;
	(void)c;
	lss_push(lexer, LSTATE_DQUOTE);
	ret = (1 << LEXER_RET_CREATE);
	ret |= (1 << LEXER_RET_CONT);
	return (ret);
}

int	lexer_create_squote(t_lexer *lexer, t_token *token, char c)
{
	int	ret;

	(void)token;
	(void)c;
	lss_push(lexer, LSTATE_SQUOTE);
	ret = (1 << LEXER_RET_CREATE);
	ret |= (1 << LEXER_RET_CONT);
	return (ret);
}
