/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:19:01 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/10 08:55:59 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "21sh.h"

int	set_pipeline(t_ast *instr)
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
	if (instr->pipes_in[PIPE_PARENT][STDOUT_FILENO] != -1)
		close(instr->pipes_in[PIPE_PARENT][STDOUT_FILENO]);
	if (instr->pipes_in[PIPE_NODE][STDOUT_FILENO] != -1)
		close(instr->pipes_in[PIPE_NODE][STDOUT_FILENO]);
	if (instr->pipes_in[PIPE_NODE][STDIN_FILENO] != -1)
		close(instr->pipes_in[PIPE_NODE][STDIN_FILENO]);
	if (instr->pipes_out[PIPE_PARENT][STDIN_FILENO] != -1)
		close(instr->pipes_out[PIPE_PARENT][STDIN_FILENO]);
	if (instr->pipes_out[PIPE_NODE][STDOUT_FILENO] != -1)
		close(instr->pipes_out[PIPE_NODE][STDOUT_FILENO]);
	if (instr->pipes_out[PIPE_NODE][STDIN_FILENO] != -1)
		close(instr->pipes_out[PIPE_NODE][STDIN_FILENO]);
	return (0);
}
