/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 18:52:02 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/24 21:37:25 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "test.h"
#include "expr.h"

static const t_test_desc	g_test_desc_unary[] =
{
	{"-b", &expr_b},
	{"-c", &expr_c},
	{"-d", &expr_d},
	{"-e", &expr_e},
	{"-f", &expr_f},
	{"-g", &expr_g},
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
	{"-z", &expr_n}
};

static const t_test_desc	g_test_desc_binary[] =
{
	{"==", &expr_equal},
	{"!=", &expr_not_equal},
	{"-eq", &expr_eq},
	{"-ne", &expr_ne},
	{"-gt", &expr_gt},
	{"-ge", &expr_ge},
	{"-lt", &expr_lt},
	{"-le", &expr_le}
};

t_test_op				get_unary_op(char *s)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_test_desc_unary) / sizeof(*g_test_desc_unary))
	{
		if (!ft_strcmp(g_test_desc_unary[i].desc, s))
			return (g_test_desc_unary[i].test);
		++i;
	}
	return (NULL);
}

t_test_op				get_binary_op(char *s)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_test_desc_binary) / sizeof(*g_test_desc_binary))
	{
		if (!ft_strcmp(g_test_desc_binary[i].desc, s))
			return (g_test_desc_binary[i].test);
		++i;
	}
	return (NULL);
}
