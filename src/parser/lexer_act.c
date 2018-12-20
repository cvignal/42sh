/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:46:31 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/15 11:09:29 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"
#include "ast.h"

int		lexer_add(t_lexer *lexer, t_token *token, char c)
{
	int	ret;

	(void)lexer;
	ret = 0;
	token->type = TT_WORD;
	if (add_to_token(token, c))
		ret |= (1 << LEXER_RET_ERROR);
	ret |= (1 << LEXER_RET_CONT);
	return (ret);
}

int		lexer_pass(t_lexer *lexer, t_token *token, char c)
{
	(void)token;
	(void)c;
	(void)lexer;
	return (1 << LEXER_RET_CONT);
}

int		lexer_cut(t_lexer *lexer, t_token *token, char c)
{
	(void)token;
	(void)c;
	lexer->state = LSTATE_NONE;
	return (1 << LEXER_RET_CUT);
}

int		lexer_create(t_lexer *lexer, t_token *token, char c)
{
	(void)token;
	(void)c;
	lexer->state = LSTATE_WORD;
	return (1 << LEXER_RET_CREATE);
}
