/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 13:01:03 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/28 18:02:50 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"

int		exec_if(t_shell *shell, t_ast *ast)
{
	if (shell->ctrlc)
		return (0);
	prepare_redirs(shell, ast);
	((t_ast *)ast->data)->exec(shell, ast->data);
	wait_loop(shell, ast->data);
	if (((t_ast *)ast->data)->ret == 0)
	{
		ast->left->exec(shell, ast->left);
		wait_loop(shell, ast->left);
		set_ret(shell, ast, ast->left->ret);
		reset_redirs(shell, ast);
		return (ast->left->ret);
	}
	else if (ast->right)
	{
		ast->right->exec(shell, ast->right);
		wait_loop(shell, ast->right);
		set_ret(shell, ast, ast->right->ret);
		reset_redirs(shell, ast);
		return (ast->right->ret);
	}
	reset_redirs(shell, ast);
	return (0);
}

void	free_if(t_ast *ast)
{
	if (ast->right)
		ast->right->del(ast->right);
	if (ast->left)
		ast->left->del(ast->left);
	if (ast->data)
		((t_ast *)ast->data)->del(ast->data);
	free_ast(ast);
}
