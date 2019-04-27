/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_escaped.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 08:40:27 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/27 18:27:39 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "libft.h"

int		lexer_push_escaped(t_shell *shell, t_token *token, char c)
{
	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	if (lss_push(&shell->lexer, LSTATE_ESCAPED))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CONT);
}

int		lexer_add_pop_escaped(t_shell *shell, t_token *token, char c)
{
	(void)shell;
	token->type = TT_WORD;
	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	lss_pop(&shell->lexer);
	return (1 << LEXER_RET_CONT);
}
