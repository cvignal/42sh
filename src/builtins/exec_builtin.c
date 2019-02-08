/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 11:21:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/08 21:56:23 by gchainet         ###   ########.fr       */
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

static void	reset_pipeline(int *old)
{
	dup2(old[STDIN_FILENO], STDIN_FILENO);
	dup2(old[STDOUT_FILENO], STDOUT_FILENO);
}

int			exec_builtin(t_shell *shell, t_builtin builtin, t_ast *instr)
{
	int		fd[2];

	if (expand_params(shell, ((t_command *)instr->data)->args))
		return (-1);
	prepare_pipeline(instr, fd);
	if (apply_redirs(shell, instr))
		return (-1);
	instr->ret = builtin(shell, ((t_command *)instr->data)->args);
	reset_pipeline(fd);
	return (instr->ret);
}
