/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 09:37:36 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/08 10:28:16 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"

int	lexer_push_var(t_shell *shell, t_token *token, char c)
{
	if (lss_push(&shell->lexer, LSTATE_VAR))
		return (1 << LEXER_RET_ERROR);
	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CONT);
}

int	lexer_pop_var(t_shell *shell, t_token *token, char c)
{
	(void)token;
	(void)c;
	(void)shell;
	return (0);
}
