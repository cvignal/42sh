/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 12:31:51 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/31 18:33:17 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "libft.h"

t_expr	*alloc_expr(void)
{
	t_expr	*new_expr;

	new_expr = malloc(sizeof(*new_expr));
	if (!new_expr)
		return (NULL);
	new_expr->args = NULL;
	new_expr->len = 0;
	return (new_expr);
}

void	free_expr_internal(t_expr *expr)
{
	unsigned int	i;

	if (expr->args)
	{
		i = 0;
		while (i < expr->len)
			free(expr->args[i++]);
		free(expr->args);
	}
	free(expr);
}

int		add_to_expr(t_expr *expr, char *arg)
{
	expr->args = ft_realloc(expr->args, expr->len * sizeof(*expr->args),
			(expr->len + 1) * sizeof(*expr->args));
	if (expr->args)
		expr->args[expr->len++] = arg;
	else
	{
		expr->len = 0;
		return (1);
	}
	return (0);
}

int		exec_expr_internal(t_shell *shell, t_expr *expr)
{
	t_expr_exec	exec;

	if (expr->len == 2)
		exec = get_expr(expr->args[0]);
	else if (expr->len == 3)
		exec = get_expr(expr->args[1]);
	else
		return (1);
	return (exec ? exec(shell, expr->args) : 1);
}
