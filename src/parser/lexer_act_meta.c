/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_meta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 10:50:50 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/15 12:15:39 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	lexer_add_meta(t_lexer *lexer, t_token *token, char c)
{
	int	ret;

	(void)lexer;
	ret = 0;
	if (add_to_token(token, c))
		ret |= (1 << LEXER_RET_ERROR);
	else if (!set_token_type(token))
	{
		token->len--;
		token->data[token->len] = 0;
		lexer->state = LSTATE_NONE;
		ret |= (1 << LEXER_RET_CUT);
	}
	else
		ret |= (1 << LEXER_RET_CONT);
	return (ret);
}

int	lexer_create_meta(t_lexer *lexer, t_token *token, char c)
{
	(void)token;
	(void)c;
	lexer->state = LSTATE_META;
	return (1 << LEXER_RET_CREATE);
}
