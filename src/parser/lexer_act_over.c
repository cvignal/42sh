/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_over.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 10:08:55 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/22 11:28:37 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	lexer_over(struct s_shell *shell, t_token *token, char c)
{
	(void)c;
	(void)shell;
	(void)token;
	return (1 << LEXER_RET_OVER);
}

int	lexer_more_input(t_shell *shell, t_token *token, char c)
{
	(void)shell;
	(void)token;
	(void)c;
	return (1 << LEXER_RET_MORE_INPUT);
}
