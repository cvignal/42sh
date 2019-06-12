/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 23:42:19 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/12 04:32:43 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_test_parser	g_test_parser[] =\
{
	{TEST_STATE_DEFAULT, &test_op_unary, TEST_STATE_UNARY},
	{TEST_STATE_DEFAULT, &test_arg, TEST_STATE_ARG},
	{TEST_STATE_ARG, &test_op_binary, TEST_STATE_BINARY},
	{TEST_STATE_BINARY, &test_arg, TEST_STATE_COMPLETE},
	{TEST_STATE_UNARY, &test_arg, TEST_STATE_COMPLETE}
};

static int	handle_logical_op(const char *arg, int ret)
{
	if (arg)
	{
		if (!ft_strcmp("-o", arg))
		{
			if (!ret)
				return (TEST_TRUE | TEST_SKIP);
			else
				return (TEST_EVAL);
		}
		else if (!ft_strcmp("-a", arg))
		{
			if (!ret)
				return (TEST_EVAL);
			else
				return (TEST_FALSE | TEST_SKIP);
		}
	}
	return (TEST_STATE_FAILURE);
}

static int	handle_arg(char *arg, char **expr, int state)
{
	unsigned int		k;

	k = 0;
	while (k < sizeof(g_test_parser) / sizeof(*g_test_parser))
	{
		if (g_test_parser[k].in_state == state)
		{
			if (!g_test_parser[k].action(arg, expr))
				return (g_test_parser[k].out_state);
		}
		++k;
	}
	return (TEST_STATE_FAILURE);
}

static int	exec_test_builtin(t_shell *shell, char **expr)
{
	size_t		len;
	t_expr_exec	action;

	len = 0;
	while (expr[len] && len < 3)
		++len;
	if (len == 2)
		action = get_test_action(expr[0]);
	else if (len == 3)
		action = get_test_action(expr[1]);
	else
		return (1);
	if (action)
		return (action(shell, expr));
	else
		return (1);
}

int			builtin_test(t_shell *shell, char **args)
{
	unsigned int		i;
	t_expr_state		state;
	int					ret;
	int					eval;
	char				*expr[3];

	state = TEST_STATE_DEFAULT;
	eval = 0;
	i = 0;
	ft_bzero(expr, sizeof(*expr) * 3);
	while (args[++i])
	{
		if (state == TEST_STATE_COMPLETE)
		{
			if (!(eval & TEST_SKIP))
				ret = exec_test_builtin(shell, expr);
			ft_bzero(expr, sizeof(*expr) * 3);
			eval = handle_logical_op(args[i], ret);
			state = TEST_STATE_DEFAULT;
		}
		else if (eval & TEST_FAIL || state == TEST_STATE_FAILURE)
			return (1);
		else
			state = handle_arg(args[i], expr, state);
	}
	return (exec_test_builtin(shell, expr));
}
