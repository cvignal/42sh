/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 03:43:14 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/13 08:05:30 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static const t_precedence	g_precedence[] =\
{
	{TT_PIPE, 2},
	{TT_END, 1},
	{TT_OR, 0},
	{TT_AND, 0},
	{TT_ARI_OP_EQ, 0},
	{TT_ARI_OP_PLUS, 1},
	{TT_ARI_OP_SUB, 1},
	{TT_ARI_OP_PROD, 2},
	{TT_ARI_OP_DIV, 2},
	{TT_ARI_OP_MOD, 2},
	{TT_ARI_OP_USUB, 3}
};

int		precedence(t_ttype type)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_precedence) / sizeof(*g_precedence))
	{
		if ((t_ttype)g_precedence[i].type == type)
			return (g_precedence[i].prec);
		++i;
	}
	return (-1);
}
