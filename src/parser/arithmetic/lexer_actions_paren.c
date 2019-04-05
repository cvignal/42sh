/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_actions_paren.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 23:05:50 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/05 23:59:43 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "arithmetic.h"

int	alexer_pop_paren(t_shell *shell, t_token *current, char c)
{
	(void)current;
	(void)c;
	lss_pop(&shell->lexer);
	return (1 << LEXER_RET_CONT);
}

int	alexer_push_paren(t_shell *shell, t_token *current, char c)
{
	(void)current;
	(void)c;
	if (lss_push(&shell->lexer, LSTATE_ARI_PAREN))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CONT);
}

int	alexer_check_end(t_shell *shell, t_token *current, char c)
{
	if (!current)
		return (1 << LEXER_RET_CREATE);
	if (add_to_token(current, c))
		return (1 << LEXER_RET_ERROR);
	if (!ft_strcmp("))", current->data))
	{
		lss_pop(&shell->lexer);
		return ((1 << LEXER_RET_CUT) | (1 << LEXER_RET_CONT));
	}
	return (1 << LEXER_RET_CONT);
}
