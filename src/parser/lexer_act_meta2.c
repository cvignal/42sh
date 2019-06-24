/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_act_meta2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marin </var/spool/mail/marin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 14:41:53 by marin             #+#    #+#             */
/*   Updated: 2019/06/08 15:13:05 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "parser.h"
#include "ast.h"

int	lexer_push_curly(t_shell *shell, t_token *token, char c)
{
	if (!token->len)
		token->type = TT_PAR;
	if (add_to_token(token, c))
		return (1 << LEXER_RET_ERROR);
	if (lss_push(&shell->lexer, LSTATE_CURLY))
		return (1 << LEXER_RET_ERROR);
	return (1 << LEXER_RET_CONT);
}
