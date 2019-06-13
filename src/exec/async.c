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
#include <unistd.h>

#include "shell.h"
#include "jobs.h"
#include "ast.h"

static int	exec_async_subshell(t_shell *shell, t_ast *node)
{
	pid_t pid;

	if ((pid = fork()) == -1)
		return (-1);
	if (pid == 0)
	{
		shell->is_subshell = 1;
		node->exec = exec_end;
		exec_job(shell, node, NULL);
		exit(node->ret);
	}
	if (!(node->job = ft_memalloc(sizeof(t_job))))
		return (-1);
	node->job->async = 1;
	node->pid = pid;
	register_proc(node);
	node->ret = register_job(shell, node->job);
	return (0);
}

int			exec_async(t_shell *shell, t_ast *ast)
{
	if (shell->ctrlc)
		return (0);
	if (ast->left)
	{
		if (exec_async_subshell(shell, ast->left))
			return (-1);
		if (shell->ctrlc)
			return (0);
	}
	else if (ast->right)
	{
		ast->job->async = 1;
		exec_job(shell, ast->right, ast->job);
	}
	return (0);
}
