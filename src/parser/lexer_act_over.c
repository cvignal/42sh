/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_over.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 10:08:55 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/04 14:46:55 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "parser.h"

int	lexer_over(struct s_shell *shell, t_token *token, char c)
{
	(void)c;
	(void)shell;
	(void)token;
	return (1 << LEXER_RET_OVER);
}

int	lexer_more_input_nl(t_shell *shell, t_token *token, char c)
{
	(void)shell;
	(void)c;
	if (add_to_token(token, '\n'))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_MORE_INPUT);
}

int	lexer_more_input(t_shell *shell, t_token *token, char c)
{
	(void)shell;
	(void)c;
	(void)token;
	return (1 << LEXER_RET_MORE_INPUT);
}

int	lexer_more_input_escaped(t_shell *shell, t_token *token, char c)
{
	(void)c;
	(void)token;
	lss_pop(&shell->lexer);
	return (1 << LEXER_RET_MORE_INPUT);
}
