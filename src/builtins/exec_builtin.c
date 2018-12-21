/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 11:21:38 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/21 11:34:11 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "minishell.h"

static int	pipe_builtin(t_pipeline *current)
{
	current->fd_copy[STDIN_FILENO] = dup(STDIN_FILENO);
	current->fd_copy[STDOUT_FILENO] = dup(STDOUT_FILENO);
	current->fd_copy[STDERR_FILENO] = dup(STDERR_FILENO);
	if (current->in_fd[STDIN_FILENO] != -1)
	{
		dup2(current->in_fd[STDIN_FILENO], STDIN_FILENO);
		close(current->in_fd[STDIN_FILENO]);
	}
	if (current->out_fd[STDOUT_FILENO] != -1)
	{
		dup2(current->out_fd[STDOUT_FILENO], STDOUT_FILENO);
		close(current->out_fd[STDOUT_FILENO]);
	}
	return (0);
}

static int	reset_builtin_fd(t_pipeline *current)
{
	dup2(current->fd_copy[STDIN_FILENO], STDIN_FILENO);
	close(current->fd_copy[STDIN_FILENO]);
	dup2(current->fd_copy[STDOUT_FILENO], STDOUT_FILENO);
	close(current->fd_copy[STDOUT_FILENO]);
	dup2(current->fd_copy[STDERR_FILENO], STDERR_FILENO);
	close(current->fd_copy[STDERR_FILENO]);
	return (0);
}

int	exec_builtin(t_shell *shell, t_builtin builtin, t_pipeline *current)
{
	int	ret;

	apply_redirs(current->command);
	pipe_builtin(current);
	ret = builtin(shell, current->command->args);
	reset_builtin_fd(current);
	return (ret);
}
