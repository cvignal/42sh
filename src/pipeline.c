/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:19:01 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/05 16:43:25 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"

int	set_pipeline(t_shell *shell, t_ast *instr)
{
	t_fd	*fd;

	if (instr->pipes_in[PIPE_PARENT][STDIN_FILENO] != -1)
		dup2(instr->pipes_in[PIPE_PARENT][STDIN_FILENO], STDIN_FILENO);
	if (instr->pipes_out[PIPE_PARENT][STDOUT_FILENO] != -1)
		dup2(instr->pipes_out[PIPE_PARENT][STDOUT_FILENO], STDOUT_FILENO);
	fd = shell->used_fd;
	while (fd)
	{
		if (fd->is_pipe)
			close(fd->fd);
		fd = fd->next;
	}
	return (0);
}

int	open_pipe(t_shell *shell, int *fd)
{
	int	new_fd;

	if (pipe(fd))
		return (1);
	new_fd = get_next_fd(shell);
	if (add_fd(shell, new_fd, 1) == -1)
		return (1);
	dup2(fd[0], new_fd);
	close(fd[0]);
	fd[0] = new_fd;
	new_fd = get_next_fd(shell);
	if (add_fd(shell, new_fd, 1) == -1)
		return (1);
	dup2(fd[1], new_fd);
	close(fd[1]);
	fd[1] = new_fd;
	return (0);
}
