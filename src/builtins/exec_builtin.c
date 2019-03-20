/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 11:21:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/03/20 15:25:58 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "shell.h"

static int	get_fd_copy(t_shell *shell, int fd)
{
	int		new_fd;
	int		fd_copy;

	new_fd = get_next_fd(shell);
	fd_copy = dup(fd);
	dup2(fd_copy, new_fd);
	close(fd_copy);
	if (add_fd(shell, new_fd, 0) == -1)
		return (-1);
	return (new_fd);
}

static int	prepare_pipeline(t_shell *shell, t_ast *instr, int *old)
{
	old[STDIN_FILENO] = get_fd_copy(shell, STDIN_FILENO);
	old[STDOUT_FILENO] = get_fd_copy(shell, STDOUT_FILENO);
	old[STDERR_FILENO] = get_fd_copy(shell, STDERR_FILENO);
	if (instr->pipes_in[PIPE_PARENT][STDIN_FILENO] != -1)
	{
		if (dup2(instr->pipes_in[PIPE_PARENT][STDIN_FILENO], STDIN_FILENO)
				== -1)
		{
			ft_dprintf(STDERR_FILENO, "%s: pipe creation failed\n", EXEC_NAME);
			return (1);
		}
	}
	if (instr->pipes_out[PIPE_PARENT][STDOUT_FILENO] != -1)
	{
		if (dup2(instr->pipes_out[PIPE_PARENT][STDOUT_FILENO], STDOUT_FILENO)
				== -1)
		{
			ft_dprintf(STDERR_FILENO, "%s: pipe creation failed\n", EXEC_NAME);
			return (1);
		}
	}
	return (0);
}

static void	reset_pipeline(t_shell *shell, int *old)
{
	dup2(old[STDIN_FILENO], STDIN_FILENO);
	dup2(old[STDOUT_FILENO], STDOUT_FILENO);
	dup2(old[STDERR_FILENO], STDERR_FILENO);
	remove_fd(shell, old[STDIN_FILENO]);
	close(old[STDIN_FILENO]);
	remove_fd(shell, old[STDOUT_FILENO]);
	close(old[STDOUT_FILENO]);
	remove_fd(shell, old[STDERR_FILENO]);
	close(old[STDERR_FILENO]);
}

int			exec_builtin(t_shell *shell, t_builtin builtin, t_ast *instr)
{
	int		fd[3];

	if (expand_params(shell, instr->data))
		return (-1);
	if (prepare_pipeline(shell, instr, fd))
		return (-1);
	if (apply_redirs(shell, instr))
		return (-1);
	if (prepare_redirs(shell, instr, instr))
		return (-1);
	instr->ret = builtin(shell, ((t_command *)instr->data)->args_value);
	reset_pipeline(shell, fd);
	reset_redirs(shell, instr);
	return (instr->ret);
}
