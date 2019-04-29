/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:46:52 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/28 18:47:51 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "jobs.h"
#include "ast.h"

int		exec_end(t_shell *shell, t_ast *ast)
{
	if (shell->ctrlc)
		return (0);
	if (ast->left)
	{
		if (!(ast->left->job = new_job()))
			return (-1);
		ast->left->exec(shell, ast->left);
		ast->left->ret = register_job(shell, ast->left->job);
	}
	if (ast->right)
	{
		ast->right->job = ast->job;
		ast->right->exec(shell, ast->right);
		return (ast->right->ret);
	}
	return (0);
}

void	free_end(t_ast *ast)
{
	if (ast->left)
		ast->left->del(ast->left);
	if (ast->right)
		ast->right->del(ast->right);
	free_ast(ast);
}
