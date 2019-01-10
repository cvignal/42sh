/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 12:33:46 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/28 16:29:02 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_expr_desc	g_expr_desc[] =
{
	{"-a", &expr_a},
	{"-b", &expr_b},
	{"-c", &expr_c},
	{"-d", &expr_d},
	{"-e", &expr_e},
	{"-f", &expr_f},
	{"-g", &expr_g},
	{"-h", &expr_h},
	{"-k", &expr_k},
	{"-p", &expr_p},
	{"-r", &expr_r},
	{"-s", &expr_s},
	{"-t", &expr_t},
	{"-u", &expr_u},
	{"-w", &expr_w},
	{"-x", &expr_x},
	{"-G", &expr_g_cap},
	{"-L", &expr_l_cap},
	{"-N", &expr_n_cap},
	{"-O", &expr_o_cap},
	{"-S", &expr_s_cap},
	{"-ef", &expr_ef},
	{"-nt", &expr_nt},
	{"-ot", &expr_ot},
	{"-v", &expr_v},
	{"-n", &expr_n},
	{"==", &expr_equal},
	{"=", &expr_equal},
	{"!=", &expr_not_equal},
	{"<", &expr_lower},
	{"-eq", &expr_eq},
	{"-ne", &expr_ne},
	{"-lt", &expr_lt},
	{"-le", &expr_le},
	{"-gt", &expr_gt},
	{"-gt", &expr_ge}
};

t_expr_exec	get_expr(const char *s)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_expr_desc) / sizeof(*g_expr_desc))
	{
		if (!ft_strcmp(g_expr_desc[i].desc, s))
			return (g_expr_desc[i].exec);
		++i;
	}
	return (NULL);
}
