/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 07:46:37 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/03 00:31:53 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "ast.h"

int			set_node_pipes(t_shell *shell, t_ast *ast)
{
	int		pipe_fd[2];

	if (open_pipe(shell, pipe_fd))
		return (1);
	ast->pipes_in[PIPE_NODE][STDIN_FILENO] = pipe_fd[0];
	ast->pipes_in[PIPE_NODE][STDOUT_FILENO] = pipe_fd[1];
	ast->pipes_out[PIPE_NODE][STDIN_FILENO] = pipe_fd[0];
	ast->pipes_out[PIPE_NODE][STDOUT_FILENO] = pipe_fd[1];
	propagate_pipe_left(ast, ast->left);
	ast->right->pipes_in[PIPE_PARENT][STDIN_FILENO] =\
		ast->pipes_out[PIPE_NODE][STDIN_FILENO];
	ast->right->pipes_in[PIPE_PARENT][STDOUT_FILENO] =\
		ast->pipes_out[PIPE_NODE][STDOUT_FILENO];
	ast->right->pipes_out[PIPE_PARENT][STDIN_FILENO] =\
		ast->pipes_out[PIPE_PARENT][STDIN_FILENO];
	ast->right->pipes_out[PIPE_PARENT][STDOUT_FILENO] =\
		ast->pipes_out[PIPE_PARENT][STDOUT_FILENO];
	return (0);
}

static void	close_all_pipes(t_shell *shell, t_ast *ast)
{
	if (ast->pipes_in[PIPE_NODE][STDIN_FILENO] != -1)
	{
		remove_fd(shell, ast->pipes_in[PIPE_NODE][STDIN_FILENO]);
		close(ast->pipes_in[PIPE_NODE][STDIN_FILENO]);
	}
	if (ast->pipes_in[PIPE_NODE][STDOUT_FILENO] != -1)
	{
		remove_fd(shell, ast->pipes_in[PIPE_NODE][STDOUT_FILENO]);
		close(ast->pipes_in[PIPE_NODE][STDOUT_FILENO]);
	}
	if (ast->pipes_out[PIPE_NODE][STDIN_FILENO] != -1)
	{
		remove_fd(shell, ast->pipes_out[PIPE_NODE][STDIN_FILENO]);
		close(ast->pipes_out[PIPE_NODE][STDIN_FILENO]);
	}
	if (ast->pipes_out[PIPE_NODE][STDOUT_FILENO] != -1)
	{
		remove_fd(shell, ast->pipes_out[PIPE_NODE][STDOUT_FILENO]);
		close(ast->pipes_out[PIPE_NODE][STDOUT_FILENO]);
	}
}

void		set_pipeline_ret(t_ast *ast)
{
	if (ast && ast->type == TT_PIPE)
	{
		set_pipeline_ret(ast->left);
		ast->ret = ast->right->ret;
	}
}

int			exec_pipeline(t_shell *shell, t_ast *ast)
{
	if (set_node_pipes(shell, ast))
	{
		ft_dprintf(2, "%s: Unable to create pipe\n", EXEC_NAME);
		return (1);
	}
	ast->left->flags |= CMD_FORK;
	exec_job(shell, ast->left, ast->job);
	if (shell->ctrlc)
		return (0);
	ast->right->flags |= CMD_FORK;
	exec_job(shell, ast->right, ast->job);
	close_all_pipes(shell, ast);
	return (0);
}

void		free_pipeline(t_ast *ast)
{
	if (ast->left)
		ast->left->del(ast->left);
	if (ast->right)
		ast->right->del(ast->right);
	free_ast(ast);
}
