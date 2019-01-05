/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 11:21:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/03 18:18:39 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "21sh.h"

static int	reset_builtin_fd(t_ast *instr)
{
	dup2(instr->old_fds[STDIN_FILENO], STDIN_FILENO);
	dup2(instr->old_fds[STDOUT_FILENO], STDOUT_FILENO);
	dup2(instr->old_fds[STDERR_FILENO], STDERR_FILENO);
	return (0);
}

static int	set_old_fd(t_ast *instr)
{
	instr->old_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	instr->old_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	instr->old_fds[STDERR_FILENO] = dup(STDERR_FILENO);
	return (0);
}

static int	prepare_pipeline(t_ast *instr)
{
	dup2(instr->pipes_in[PIPE_PARENT][STDIN_FILENO], STDIN_FILENO);
	close(instr->pipes_in[PIPE_PARENT][STDIN_FILENO]);
	dup2(instr->pipes_out[PIPE_PARENT][STDOUT_FILENO], STDOUT_FILENO);
	close(instr->pipes_out[PIPE_PARENT][STDOUT_FILENO]);
	return (0);
}

int			exec_builtin(t_shell *shell, t_builtin builtin, t_ast *instr)
{
	int	ret;

	set_old_fd(instr);
	apply_redirs(shell, instr->data);
	prepare_pipeline(instr);
	ret = builtin(shell, ((t_command *)instr->data)->args);
	reset_builtin_fd(instr);
	return (ret);
}
