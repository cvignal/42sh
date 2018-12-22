/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_over.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 10:08:55 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/22 10:19:39 by gchainet         ###   ########.fr       */
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
