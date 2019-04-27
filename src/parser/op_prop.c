/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_prop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 19:42:46 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/28 00:29:24 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static const t_op_prop	g_op_prop[] =\
{
	{TT_AND, 2, LEFT, 0},
	{TT_ARI_OP_AND, 2, LEFT, 1},
	{TT_ARI_OP_CMP_EQ, 2, LEFT, 2},
	{TT_ARI_OP_CMP_INF, 2, LEFT, 2},
	{TT_ARI_OP_CMP_INF_EQ, 2, LEFT, 2},
	{TT_ARI_OP_CMP_NOT_EQ, 2, LEFT, 2},
	{TT_ARI_OP_CMP_SUP, 2, LEFT, 2},
	{TT_ARI_OP_CMP_SUP_EQ, 2, LEFT, 2},
	{TT_ARI_OP_DIV, 2, LEFT, 4},
	{TT_ARI_OP_EQ, 2, LEFT, 0},
	{TT_ARI_OP_MOD, 2, LEFT, 4},
	{TT_ARI_OP_OR, 2, LEFT, 1},
	{TT_ARI_OP_PLUS, 2, LEFT, 4},
	{TT_ARI_OP_PLUS_PLUS, 1, RIGHT, 5},
	{TT_ARI_OP_PROD, 2, LEFT, 4},
	{TT_ARI_OP_SUB, 2, LEFT, 3},
	{TT_ARI_OP_SUB_SUB, 1, RIGHT, 5},
	{TT_ARI_OP_UPLUS, 1, RIGHT, 5},
	{TT_ARI_OP_USUB, 1, RIGHT, 5},
	{TT_BG, 1, RIGHT, 1},
	{TT_END, 2, LEFT, 1},
	{TT_END_UNARY, 1, RIGHT, 1},
	{TT_OR, 2, LEFT, 0},
	{TT_PIPE, 2, LEFT, 2}
};

const t_op_prop	*get_op_prop(t_ttype type)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_op_prop) / sizeof(*g_op_prop))
	{
		if (g_op_prop[i].type == type)
			return (&g_op_prop[i]);
		++i;
	}
	return (0);
}
