/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <gchainet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:57:58 by gchainet          #+#    #+#             */
/*   Updated: 2019/03/24 06:20:30 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>

#include "shell.h"
#include "parser.h"
#include "ast.h"

int		g_flag = 0;

void	local_signal(int i)
{
	(void)i;
	g_flag = 1;
}

int		exec_while(t_shell *shell, t_ast *ast)
{
	if (shell->ctrlc)
		return (0);
	((t_ast *)ast->data)->exec(shell, ast->data);
	wait_loop(ast->data);
	signal(SIGINT, local_signal);
	while (((t_ast *)ast->data)->ret == 0 && !g_flag)
	{
		ast->left->exec(shell, ast->left);
		wait_loop(ast->left);
		((t_ast *)ast->data)->exec(shell, ast->data);
		wait_loop(ast->data);
	}
	g_flag = 0;
	disable_signal(shell);
	reset_redirs(shell, ast);
	return (ast->left->ret);
}

void	free_while(t_ast *ast)
{
	if (ast->left)
		ast->left->del(ast->left);
	if (ast->data)
		((t_ast *)ast->data)->del(ast->data);
	free_ast(ast);
}
