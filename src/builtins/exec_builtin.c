/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 11:21:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/10 09:27:26 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"

static int	prepare_pipeline(t_ast *instr, int *old)
{
	old[STDIN_FILENO] = dup(STDIN_FILENO);
	old[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (instr->pipes_in[PIPE_PARENT][STDIN_FILENO] != -1)
		dup2(instr->pipes_in[PIPE_PARENT][STDIN_FILENO], STDIN_FILENO);
	if (instr->pipes_out[PIPE_PARENT][STDOUT_FILENO] != -1)
		dup2(instr->pipes_out[PIPE_PARENT][STDOUT_FILENO], STDOUT_FILENO);
	return (0);
}

int			exec_builtin(t_shell *shell, t_builtin builtin, t_ast *instr)
{
	int		fd[2];

	prepare_pipeline(instr, fd);
	apply_redirs(shell, instr);
	instr->ret = builtin(shell, ((t_command *)instr->data)->args);
	dup2(fd[STDIN_FILENO], STDIN_FILENO);
	dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
	close(fd[STDIN_FILENO]);
	close(fd[STDOUT_FILENO]);
	reset_redirs(instr);
	return (instr->ret);
}
