/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:31:21 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/07 03:04:38 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "arithmetic.h"

static const t_ari_op_desc	g_op_desc[] =\
{
	{"+", TT_ARI_OP_PLUS, &exec_ari_plus, &free_ari},
	{"-", TT_ARI_OP_SUB, &exec_ari_sub, &free_ari},
	{"*", TT_ARI_OP_PROD, &exec_ari_prod, &free_ari},
	{"/", TT_ARI_OP_DIV, &exec_ari_div, &free_ari},
	{"%", TT_ARI_OP_MOD, &exec_ari_mod, &free_ari},
	{"=", TT_ARI_OP_EQ, &exec_ari_eq, &free_ari},
	{"(", TT_OPEN_PAR, NULL, &free_ari},
	{")", TT_CLOSE_PAR, NULL, &free_ari}
};

int					is_operator_char(char c)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_op_desc) / sizeof(*g_op_desc))
	{
		if (ft_strchr(g_op_desc[i].desc, c))
			return (1);
		++i;
	}
	return (0);
}

int					get_arithmetic_token_type(const char *s)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_op_desc) / sizeof(*g_op_desc))
	{
		if (!ft_strcmp(g_op_desc[i].desc, s))
			return (g_op_desc[i].type);
		++i;
	}
	return (TT_ARI_ID);
}

int		get_arithmetic_desc(int type, t_ari_op_desc *dest)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_op_desc) / sizeof(*g_op_desc))
	{
		if (g_op_desc[i].type == type)
		{
			ft_memcpy(dest, g_op_desc + i, sizeof(*dest));
			return (0);
		}
		++i;
	}
	return (1);
}
