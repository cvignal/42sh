/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_over.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:43:07 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/27 23:45:17 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"

int	exp_lexer_error(t_shell *shell, char c , int mask)
{
	(void)shell;
	(void)c;
	(void)mask;
	return (EXP_LEXER_RET_ERROR);
}

int	exp_lexer_over(t_shell *shell, char c , int mask)
{
	(void)shell;
	(void)c;
	(void)mask;
	return (EXP_LEXER_RET_OVER);
}
