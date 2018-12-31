/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pss.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 18:06:29 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/31 15:29:42 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

int			pss_push(t_parser *parser, int state)
{
	t_pss	*new_state;

	new_state = malloc(sizeof(*new_state));
	if (!new_state)
		return (1);
	new_state->state = state;
	new_state->next = parser->pss;
	parser->pss = new_state;
	return (0);
}

int			pss_pop(t_parser *parser)
{
	int	state;
	t_pss		*tmp;

	state = parser->pss->state;
	tmp = parser->pss;
	parser->pss = parser->pss->next;
	free(tmp);
	return (state);
}
