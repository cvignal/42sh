/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 07:46:37 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/10 09:02:45 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "21sh.h"
#include "ast.h"

int			set_node_pipes(t_ast *ast)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd))
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

static void	close_all_pipes(t_ast *ast)
{
	if (ast)
	{
		close_all_pipes(ast->left);
		close_all_pipes(ast->right);
		if (ast->pipes_in[PIPE_NODE][STDIN_FILENO] != -1)
			close(ast->pipes_in[PIPE_NODE][STDIN_FILENO]);
		if (ast->pipes_in[PIPE_NODE][STDOUT_FILENO] != -1)
			close(ast->pipes_in[PIPE_NODE][STDOUT_FILENO]);
		if (ast->pipes_out[PIPE_NODE][STDIN_FILENO] != -1)
			close(ast->pipes_out[PIPE_NODE][STDIN_FILENO]);
		if (ast->pipes_out[PIPE_NODE][STDOUT_FILENO] != -1)
			close(ast->pipes_out[PIPE_NODE][STDOUT_FILENO]);
	}
}

int			exec_pipeline(t_shell *shell, t_ast *ast)
{
	if (set_node_pipes(ast))
		return (1);
	ast->left->exec(shell, ast->left);
	ast->right->exec(shell, ast->right);
	close_all_pipes(ast);
	wait_loop(ast);
	return (ast->right->ret);
}

void		free_pipeline(t_ast *ast)
{
	ast->left->del(ast->left);
	ast->right->del(ast->right);
	free_ast(ast);
}
