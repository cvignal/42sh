/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:46:31 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 09:48:56 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "libft.h"
#include "ast.h"

int		lexer_add(t_shell *shell, t_token *token, char c)
{
	(void)shell;
	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CONT);
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

int		lexer_pop_pass(t_shell *shell, t_token *token, char c)
{
	(void)token;
	(void)c;
	lss_pop(&shell->lexer);
	return (1 << LEXER_RET_CONT);
}
