/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:57:58 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/16 10:32:56 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "parser.h"
#include "ast.h"

int		exec_while(t_shell *shell, t_ast *ast)
{
	if (shell->ctrlc)
		return (0);
	((t_ast *)ast->data)->exec(shell, ast->data);
	wait_loop(ast->data);
	while (((t_ast *)ast->data)->ret == 0)
	{
		ast->left->exec(shell, ast->left);
		wait_loop(ast->left);
		((t_ast *)ast->data)->exec(shell, ast->data);
		wait_loop(ast->data);
	}
	reset_redirs(shell, ast);
	return (ast->left->ret);
}

void	free_while(t_ast *ast)
{
	if (ast->left)
		ast->left->del(ast->left);
	free_ast(ast);
}
