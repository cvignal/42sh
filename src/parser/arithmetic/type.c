/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:31:21 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/07 00:46:56 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "arithmetic.h"

static const t_ari_op_desc	g_op_desc[] =\
{
	{"+", TT_ARI_OP_PLUS, &stub_exec_ari, &stub_del_ari},
	{"-", TT_ARI_OP_SUB, &stub_exec_ari, &stub_del_ari},
	{"*", TT_ARI_OP_PROD, &stub_exec_ari, &stub_del_ari},
	{"/", TT_ARI_OP_DIV, &stub_exec_ari, &stub_del_ari},
	{"%", TT_ARI_OP_MOD, &stub_exec_ari, &stub_del_ari},
	{"=", TT_ARI_OP_EQ, &stub_exec_ari, &stub_del_ari},
	{"(", TT_OPEN_PAR, &stub_exec_ari, &stub_del_ari},
	{")", TT_CLOSE_PAR, &stub_exec_ari, &stub_del_ari}
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
