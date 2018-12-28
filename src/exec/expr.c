/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 13:25:42 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 12:42:09 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		exec_expr(t_shell *shell, struct s_ast *ast)
{
	(void)shell;
	return (exec_expr_internal(shell, ast->data));
}

void	free_expr(struct s_ast *ast)
{
	free_expr_internal(ast->data);
	free(ast);
}
