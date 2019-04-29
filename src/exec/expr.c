/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 13:25:42 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 07:32:23 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		exec_expr(t_shell *shell, struct s_ast *ast)
{
	if (shell->ctrlc)
		return (0);
	ast->ret = exec_expr_internal(shell, ast->data);
	return (ast->ret);
}

void	free_expr(struct s_ast *ast)
{
	free_expr_internal(ast->data);
	free_ast(ast);
}
