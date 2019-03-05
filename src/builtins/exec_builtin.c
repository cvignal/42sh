/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 11:21:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/03/05 16:52:36 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"

static int	prepare_pipeline(t_ast *instr, int *old)
{
	old[STDIN_FILENO] = dup(STDIN_FILENO);
	old[STDOUT_FILENO] = dup(STDOUT_FILENO);
	old[STDERR_FILENO] = dup(STDERR_FILENO);
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

static void	reset_pipeline(int *old)
{
	if (dup2(old[STDIN_FILENO], STDIN_FILENO) == -1)
		ft_dprintf(2, "Error on restoring stdin\n");
	if (dup2(old[STDOUT_FILENO], STDOUT_FILENO) == -1)
		ft_dprintf(2, "Error on restoring stdout\n");
	if (dup2(old[STDERR_FILENO], STDERR_FILENO) == -1)
		ft_dprintf(2, "Error on restoring stderr\n");
	if (close(old[STDIN_FILENO]) == -1)
		ft_dprintf(2, "Error closing old stdin\n");
	if (close(old[STDOUT_FILENO]) == -1)
		ft_dprintf(2, "Error closing old stdout\n");
	if (close(old[STDERR_FILENO]) == -1)
		ft_dprintf(2, "Error closing old stderr\n");
}

int			exec_builtin(t_shell *shell, t_builtin builtin, t_ast *instr)
{
	int		fd[3];

	if (expand_params(shell, instr->data))
		return (-1);
	if (prepare_pipeline(instr, fd))
		return (-1);
	if (apply_redirs(shell, instr))
		return (-1);
	if (prepare_redirs(shell, instr, instr))
		return (-1);
	instr->ret = builtin(shell, ((t_command *)instr->data)->args_value);
	reset_pipeline(fd);
	reset_redirs(shell, instr);
	return (instr->ret);
}
