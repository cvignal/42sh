/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 00:25:35 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/12 04:37:05 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expr.h"

static const t_expr_desc g_test_desc_unary[] =\
{
	{"-b", &expr_b},
	{"-c", &expr_c},
	{"-d", &expr_d},
	{"-e", &expr_d},
	{"-f", &expr_f},
	{"-h", &expr_h},
	{"-L", &expr_l_cap},
	{"-n", &expr_n},
	{"-p", &expr_p},
	{"-r", &expr_r},
	{"-S", &expr_s_cap},
	{"-s", &expr_s},
	{"-t", &expr_t},
	{"-u", &expr_u},
	{"-w", &expr_w},
	{"-x", &expr_x},
	{"-z", &expr_z}
};

static const t_expr_desc	g_test_desc_binary[] =\
{
	{"=", &expr_equal},
	{"!=", &expr_not_equal},
	{"-eq", &expr_eq},
	{"-ne", &expr_ne},
	{"-gt", &expr_gt},
	{"-ge", &expr_ge},
	{"-lt", &expr_lt},
	{"-le", &expr_le}
};

int	test_arg(char *s, char **arg)
{
	unsigned int	i;

	if (s[0] == '-')
		return (1);
	i = 0;
	while (arg[i])
		++i;
	arg[i] = s;
	return (0);
}

int	test_op_unary(char *s, char **arg)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_test_desc_unary) / sizeof(*g_test_desc_unary))
	{
		if (!ft_strcmp(g_test_desc_unary[i].desc, s))
		{
			arg[0] = s;
			return (0);
		}
		++i;
	}
	return (1);
}

int	test_op_binary(char *s, char **arg)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_test_desc_binary) / sizeof(*g_test_desc_binary))
	{
		if (!ft_strcmp(g_test_desc_binary[i].desc, s))
		{
			arg[1] = s;
			return (0);
		}
		++i;
	}
	return (1);
}

t_expr_exec	get_test_action(char *s)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_test_desc_binary) / sizeof(*g_test_desc_binary))
	{
		if (!ft_strcmp(g_test_desc_binary[i].desc, s))
			return (g_test_desc_binary[i].exec);
		++i;
	}
	i = 0;
	while (i < sizeof(g_test_desc_unary) / sizeof(*g_test_desc_unary))
	{
		if (!ft_strcmp(g_test_desc_unary[i].desc, s))
			return (g_test_desc_unary[i].exec);
		++i;
	}
	return (NULL);
}
