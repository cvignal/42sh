/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:46:52 by agrouard          #+#    #+#             */
/*   Updated: 2019/04/28 18:47:51 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "jobs.h"
#include "ast.h"

static int	do_async(t_shell *shell, t_ast *node)
{
	if (!(node->job = new_job()))
		return (-1);
	node->job->async = 1;
	node->ret = node->exec(shell, node);
	if (node->job->proc)
		node->ret = register_job(shell, node->job);
	else
		free(node->job);
	return (0);
}

int			exec_async(t_shell *shell, t_ast *ast)
{
	if (shell->ctrlc)
		return (0);
	if (ast->left)
	{
		do_async(shell, ast->left);
		exec_job(shell, ast->right, ast->job);
	}
	else if (ast->right)
	{
		ast->job->async = 1;
		exec_job(shell, ast->right, ast->job);
	}
	return (0);
}
