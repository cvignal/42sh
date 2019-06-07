/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:46:52 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/03 00:21:51 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "ast.h"

int		exec_end(t_shell *shell, t_ast *ast)
{
	if (shell->ctrlc)
		return (0);
	if (ast->left)
	{
		ast->left->exec(shell, ast->left);
		wait_loop(shell, ast->left);
	}
	if (ast->right)
	{
		ast->right->exec(shell, ast->right);
		wait_loop(shell, ast->right);
	}
	return ((ast->ret = 0));
}

void	free_end(t_ast *ast)
{
	if (ast->left)
		ast->left->del(ast->left);
	if (ast->right)
		ast->right->del(ast->right);
	free_ast(ast);
}
