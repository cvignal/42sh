/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pss.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 18:06:29 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/07 09:00:56 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"
#include "ast.h"
#include "libft.h"

int			pss_push(t_parser *parser, int state)
{
	t_pss	*new_state;

	new_state = malloc(sizeof(*new_state));
	if (!new_state)
		return (1);
	ft_bzero(new_state, sizeof(*new_state));
	new_state->state = state;
	new_state->next = parser->pss;
	parser->pss = new_state;
	return (0);
}

t_ast		*pss_pop(t_parser *parser)
{
	t_ast		*token;
	t_pss		*tmp;

	token = parser->pss->ret;
	tmp = parser->pss;
	parser->pss = parser->pss->next;
	free(tmp);
	return (token);
}
