/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:48:09 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 01:59:15 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "arithmetic.h"

int	alexer_input_error(t_shell *shell, t_token *current, char c)
{
	(void)shell;
	(void)current;
	(void)c;
	return (1 << LEXER_RET_ERROR);
}

int	alexer_create(t_shell *shell, t_token *current, char c)
{
	int	state;

	(void)current;
	if (ft_isalnum(c) || c == '$' || c == '_')
		state = LSTATE_ARI_ID;
	else
		state = LSTATE_ARI_OP;
	if (lss_push(&shell->lexer, state))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CREATE);
}

int	alexer_cut(t_shell *shell, t_token *current, char c)
{
	(void)current;
	(void)c;
	if (lss_pop(&shell->lexer) != LSTATE_ARI_FIRST_PASS)
		current->type = get_arithmetic_token_type(current->data);
	return (1 << LEXER_RET_CUT);
}

int	alexer_add(t_shell *shell, t_token *current, char c)
{
	(void)shell;
	if (add_to_token(current, c))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CONT);
}

int	alexer_try_op(t_shell *shell, t_token *current, char c)
{
	int				type;

	(void)shell;
	if (add_to_token(current, c))
		return (1 << LEXER_RET_ERROR);
	type = get_arithmetic_token_type(current->data);
	if (type != TT_ARI_ID && type != TT_ARI_NUMBER)
	{
		current->type = type;
		return (1 << LEXER_RET_CONT);
	}
	((char *)current->data)[--current->len] = 0;
	lss_pop(&shell->lexer);
	return (1 << LEXER_RET_CUT);
}
