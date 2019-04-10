/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:16:35 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/02 15:50:47 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "expand.h"
#include "libft.h"

static int	allocation_error(void)
{
	ft_dprintf(2, "%s: unable to allocate memory\n", EXEC_NAME);
	return (1);
}

static int	expand_expr_three_args(t_shell *shell, t_expr *expr)
{
	int		error;

	error = 0;
	if (!expr->args_value[1])
	{
		expr->args_value[1] = ft_strdup(expr->args[1]);
		if (!expr->args_value[1])
			return (1);
	}
	if (expr->args_value[0])
		free(expr->args_value[0]);
	expr->args_value[0] = expand(shell, expr->args[0], &error);
	if (error)
		return (1);
	if (expr->args_value[2])
		free(expr->args_value[2]);
	expr->args_value[2] = expand(shell, expr->args[2], &error);
	if (error)
		return (1);
	return (0);
}

static int	expand_expr_two_args(t_shell *shell, t_expr *expr)
{
	int		error;

	error = 0;
	if (!expr->args_value[0])
	{
		expr->args_value[0] = ft_strdup(expr->args[0]);
		if (!expr->args_value[0])
			return (1);
	}
	if (expr->args_value[1])
		free(expr->args_value[1]);
	expr->args_value[1] = expand(shell, expr->args[1], &error);
	if (error)
		return (1);
	return (0);
}

int			expand_expr(t_shell *shell, t_expr *expr)
{
	ft_bzero(&shell->exp_lexer.buffer, sizeof(shell->exp_lexer.buffer));
	ft_bzero(&shell->exp_lexer.var, sizeof(shell->exp_lexer.var));
	if (!expr->args_value)
	{
		expr->args_value = malloc(sizeof(*expr->args_value) * expr->len);
		if (!expr->args_value)
			return (1);
		ft_bzero(expr->args_value, sizeof(*expr->args_value) * expr->len);
	}
	if (expr->len == 2)
	{
		if (expand_expr_two_args(shell, expr))
			return (allocation_error());
	}
	else if (expr->len == 3)
	{
		if (expand_expr_three_args(shell, expr))
			return (allocation_error());
	}
	return (0);
}
