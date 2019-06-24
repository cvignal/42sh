/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 18:37:47 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/24 21:56:45 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "test.h"

static int	builtin_test_one_op(t_shell *shell, char **args)
{
	(void)shell;
	return (args[1] == NULL);
}

static int	builtin_test_two_op(t_shell *shell, char **args)
{
	t_test_op	op;

	if (!ft_strcmp(args[1], "!"))
		return (!builtin_test_one_op(shell, args + 1));
	else
	{
		op = get_unary_op(args[1]);
		if (op)
			return (op(shell, args + 1));
		return (1);
	}
}

static int	builtin_test_three_op(t_shell *shell, char **args)
{
	t_test_op	op;

	if (!ft_strcmp(args[1], "!"))
		return (!builtin_test_two_op(shell, args + 1));
	else
	{
		op = get_binary_op(args[2]);
		if (op)
			return (op(shell, args + 1));
		return (1);
	}
}

static int	builtin_test_four_op(t_shell *shell, char **args)
{
	if (!ft_strcmp(args[1], "!"))
		return (!builtin_test_three_op(shell, args + 1));
	return (1);
}

int		builtin_test(t_shell *shell, char **args)
{
	size_t	args_len;

	args_len = 0;
	while (args[args_len])
		++args_len;
	if (args_len == 1)
		return (1);
	else if (args_len == 2)
		return (builtin_test_one_op(shell, args));
	else if (args_len == 3)
		return (builtin_test_two_op(shell, args));
	else if (args_len == 4)
		return (builtin_test_three_op(shell, args));
	else if (args_len == 5)
		return (builtin_test_four_op(shell, args));
	else
		return (1);
	return (0);
}
