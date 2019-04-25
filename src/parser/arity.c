/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arity.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 01:18:03 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/26 01:39:05 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static const t_arity	g_arity[] =\
{
	{TT_AND, 2},
	{TT_ARI_OP_CMP_EQ, 2},
	{TT_ARI_OP_CMP_INF, 2},
	{TT_ARI_OP_CMP_INF_EQ, 2},
	{TT_ARI_OP_CMP_NOT_EQ, 2},
	{TT_ARI_OP_CMP_SUP, 2},
	{TT_ARI_OP_CMP_SUP_EQ, 2},
	{TT_ARI_OP_DIV, 2},
	{TT_ARI_OP_EQ, 2},
	{TT_ARI_OP_MOD, 2},
	{TT_ARI_OP_PLUS, 2},
	{TT_ARI_OP_PLUS_PLUS, 1},
	{TT_ARI_OP_PROD, 2},
	{TT_ARI_OP_SUB, 2},
	{TT_ARI_OP_SUB_SUB, 1},
	{TT_ARI_OP_UPLUS, 1},
	{TT_ARI_OP_USUB, 1},
	{TT_BG, 1},
	{TT_END, 2},
	{TT_END_UNARY, 1},
	{TT_OR, 2},
	{TT_PIPE, 2},
};

int	get_arity(t_ttype type)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_arity) / sizeof(*g_arity))
	{
		if (g_arity[i].type == type)
			return (g_arity[i].arity);
		++i;
	}
	return (0);
}
