/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lss.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 08:56:06 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/22 09:00:48 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

int lss_push(t_lexer *lexer, t_lstate state)
{
	t_lss	*new_state;

	new_state = malloc(sizeof(*new_state));
	if (!new_state)
		return (1);
	new_state->state = state;
	new_state->next = lexer->lss;
	lexer->lss = new_state;
	return (0);
}

t_lstate	lss_pop(t_lexer *lexer)
{
	t_lss		*tmp;
	t_lstate	ret;

	if (!lexer->lss)
		return (LSTATE_NONE);
	tmp = lexer->lss->next;
	ret = lexer->lss->state;
	free(lexer->lss);
	lexer->lss = tmp;
	return (ret);
}
