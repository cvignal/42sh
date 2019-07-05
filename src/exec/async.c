/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:46:52 by agrouard          #+#    #+#             */
/*   Updated: 2019/07/05 01:04:43 by gchainet         ###   ########.fr       */
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
		pid = getpid();
		setpgid(pid, pid);
		shell->is_subshell = 1;
		enable_signal(SIGNAL_SIGINT | SIGNAL_OTHER);
		exec_job(shell, node, NULL);
		exit(node->ret);
	}
	if (!(node->job = new_job()))
		return (-1);
	node->job->async = 1;
	node->pid = pid;
	register_proc(node);
	node->ret = register_job(shell, node->job);
	return (0);
}

static int	do_exec_async(t_shell *shell, t_ast *node)
{
	if (node->type == TT_AND ||node->type == TT_OR)
		return (exec_async_subshell(shell, node));
	if (!(node->job = new_job()))
		return (-1);
	node->job->async = 1;
	if (node->exec(shell, node))
		return (-1);
	set_ret(shell, node, register_job(shell, node->job));
	return (0);
}

int			exec_async(t_shell *shell, t_ast *ast)
{
	if (shell->ctrlc)
		return (0);
	if (!ast->left)
	{
		ast->left = ast->right;
		ast->right = NULL;
	}
	if (do_exec_async(shell, ast->left))
		return (-1);
	if (shell->ctrlc)
		return (0);
	if (ast->right)
		return (exec_job(shell, ast->right, ast->job));
	return (0);
}
