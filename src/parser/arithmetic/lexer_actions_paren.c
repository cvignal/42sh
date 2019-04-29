/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_actions_paren.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 23:05:50 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 02:00:25 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "arithmetic.h"

int	alexer_count_paren(t_shell *shell, t_token *current, char c)
{
	int				count;
	unsigned int	i;

	(void)shell;
	if (add_to_token(current, c))
		return (1 << LEXER_RET_ERROR);
	count = 0;
	i = 0;
	while (i < current->len)
	{
		if (((char *)current->data)[i] == '(')
			++count;
		else if (((char *)current->data)[i] == ')')
			--count;
		++i;
	}
	if (!count)
	{
		lss_pop(&shell->lexer);
		return ((1 << LEXER_RET_CUT) | (1 << LEXER_RET_CONT));
	}
	return (1 << LEXER_RET_CONT);
}
