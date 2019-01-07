/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 11:21:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/07 09:51:53 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "21sh.h"

static int	prepare_pipeline(t_ast *instr)
{
	if (instr->pipes_in[PIPE_PARENT][STDIN_FILENO] != -1)
	{
		dup2(instr->pipes_in[PIPE_PARENT][STDIN_FILENO], STDIN_FILENO);
		close(instr->pipes_in[PIPE_PARENT][STDIN_FILENO]);
	}
	if (instr->pipes_out[PIPE_PARENT][STDOUT_FILENO] != -1)
	{
		dup2(instr->pipes_out[PIPE_PARENT][STDOUT_FILENO], STDOUT_FILENO);
		close(instr->pipes_out[PIPE_PARENT][STDOUT_FILENO]);
	}
	return (0);
}

int			exec_builtin(t_shell *shell, t_builtin builtin, t_ast *instr)
{
	prepare_pipeline(instr);
	apply_redirs(shell, instr);
	instr->ret = builtin(shell, ((t_command *)instr->data)->args);
	return (instr->ret);
}
