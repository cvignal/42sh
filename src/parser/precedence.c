/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 03:43:14 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/26 01:46:36 by gchainet         ###   ########.fr       */
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
	{TT_ARI_OP_CMP_EQ, 1},
	{TT_ARI_OP_CMP_NOT_EQ, 1},
	{TT_ARI_OP_CMP_INF_EQ, 1},
	{TT_ARI_OP_CMP_INF, 1},
	{TT_ARI_OP_CMP_SUP, 1},
	{TT_ARI_OP_CMP_SUP_EQ, 1},
	{TT_ARI_OP_PLUS, 2},
	{TT_ARI_OP_SUB, 2},
	{TT_ARI_OP_PROD, 3},
	{TT_ARI_OP_DIV, 3},
	{TT_ARI_OP_MOD, 3},
	{TT_ARI_OP_USUB, 4},
	{TT_ARI_OP_PLUS_PLUS, 4},
	{TT_ARI_OP_SUB_SUB, 4}
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
