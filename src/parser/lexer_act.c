/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:46:31 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 18:45:25 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "libft.h"
#include "ast.h"

int		lexer_add(t_shell *shell, t_token *token, char c)
{
	int	ret;

	(void)shell;
	ret = 0;
	token->type = TT_WORD;
	if (add_to_token(token, c))
		ret |= (1 << LEXER_RET_ERROR);
	ret |= (1 << LEXER_RET_CONT);
	return (ret);
}

int		lexer_pass(t_shell *shell, t_token *token, char c)
{
	(void)token;
	(void)c;
	(void)shell;
	return (1 << LEXER_RET_CONT);
}

int		lexer_cut(t_shell *shell, t_token *token, char c)
{
	(void)token;
	(void)c;
	lss_pop(&shell->lexer);
	return (1 << LEXER_RET_CUT);
}

int		lexer_create(t_shell *shell, t_token *token, char c)
{
	(void)token;
	(void)c;
	if (lss_push(&shell->lexer, LSTATE_WORD))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CREATE);
}

int		lexer_cut_pass(t_shell *shell, t_token *token, char c)
{
	int	ret;

	(void)token;
	(void)c;
	lss_pop(&shell->lexer);
	ret = (1 << LEXER_RET_CUT);
	ret |= (1 << LEXER_RET_CONT);
	return (ret);
}
