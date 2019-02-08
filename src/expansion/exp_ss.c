/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_ss.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 21:15:17 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/08 21:18:18 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "expand.h"

int		exp_ss_push(t_exp_lexer *lexer, t_exp_state state)
{
	t_exp_ss	*new_state;

	new_state = malloc(sizeof(*new_state));
	if (!new_state)
		return (1);
	new_state->state = state;
	new_state->next = lexer->state;
	lexer->state = new_state;
	return (0);
}

void	exp_ss_pop(t_exp_lexer *lexer)
{
	t_exp_ss	*tmp;

	tmp = lexer->state;
	if (tmp)
	{
		lexer->state = lexer->state->next;
		free(tmp);
	}
}
