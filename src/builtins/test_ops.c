/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 18:52:02 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/24 19:01:40 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "test.h"

static int				test_debug_unary(t_shell *shell, char **args)
{
	(void)shell;
	ft_printf("unary %s %s\n", args[1], args[2]);
	return (0);
}

static int				test_debug_binary(t_shell *shell, char **args)
{
	(void)shell;
	ft_printf("binary %s %s %s\n", args[1], args[2], args[3]);
	return (0);
}

static const t_test_desc	g_test_desc_unary[] =
{
	{"-b", &test_debug_unary},
	{"-c", &test_debug_unary},
	{"-d", &test_debug_unary},
	{"-e", &test_debug_unary},
	{"-f", &test_debug_unary},
	{"-g", &test_debug_unary},
	{"-h", &test_debug_unary},
	{"-L", &test_debug_unary},
	{"-n", &test_debug_unary},
	{"-p", &test_debug_unary},
	{"-r", &test_debug_unary},
	{"-S", &test_debug_unary},
	{"-s", &test_debug_unary},
	{"-t", &test_debug_unary},
	{"-u", &test_debug_unary},
	{"-w", &test_debug_unary},
	{"-x", &test_debug_unary},
	{"-z", &test_debug_unary}
};

static const t_test_desc	g_test_desc_binary[] =
{
	{"==", &test_debug_binary},
	{"!=", &test_debug_binary},
	{"-eq", &test_debug_binary},
	{"-ne", &test_debug_binary},
	{"-gt", &test_debug_binary},
	{"-ge", &test_debug_binary},
	{"-lt", &test_debug_binary},
	{"-le", &test_debug_binary}
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
