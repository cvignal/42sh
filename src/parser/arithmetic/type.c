/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:31:21 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/06 00:13:38 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "arithmetic.h"

static const t_ari_op_desc	g_op_desc[] =\
{
	{"+", TT_ARI_OP_PLUS},
	{"-", TT_ARI_OP_SUB},
	{"*", TT_ARI_OP_PROD},
	{"/", TT_ARI_OP_DIV},
	{"%", TT_ARI_OP_MOD},
	{"=", TT_ARI_OP_EQ}
};

int	is_operator_char(char c)
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

int	get_arithmetic_token_type(const char *s)
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
