/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 11:21:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/28 17:58:27 by cvignal          ###   ########.fr       */
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

static int	save_builtin_fds(t_shell *shell, int *old)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		old[i] = get_fd_copy(shell, i);
		++i;
	}
	return (0);
}

static void	reset_builtin_fds(t_shell *shell, int *old)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		dup2(old[i], i);
		remove_fd(shell, old[i]);
		close(old[i]);
		++i;
	}
}

static int	exec_builtin_internal(t_shell *shell, t_builtin builtin,
		t_ast *instr)
{
	set_pipeline(shell, instr);
	if (apply_redirs(shell, instr))
		return (127);
	return (builtin(shell, ((t_command *)instr->data)->args_value));
}

int			exec_builtin(t_shell *shell, t_builtin builtin, t_ast *instr)
{
	int		fd[3];
	pid_t	pid;

	if (instr->pipes_in[PIPE_PARENT][STDIN_FILENO] != -1
			|| instr->pipes_out[PIPE_PARENT][STDOUT_FILENO] != -1)
	{
		if (!(pid = fork()))
			exit(exec_builtin_internal(shell, builtin, instr));
		instr->pid = pid;
	}
	else
	{
		save_builtin_fds(shell, fd);
		instr->ret = exec_builtin_internal(shell, builtin, instr);
		reset_builtin_fds(shell, fd);
		reset_redirs(shell, instr);
	}
	return (instr->ret);
}
