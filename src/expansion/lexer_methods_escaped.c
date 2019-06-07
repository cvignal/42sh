/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_escaped.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 19:50:22 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/01 21:27:17 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include "libft.h"

int	exp_lexer_push_escaped(t_shell *shell, char c, int mask)
{
	(void)c;
	(void)mask;
	shell->exp_lexer.split = 0;
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_ESCAPED))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}
