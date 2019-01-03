/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 11:21:38 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/03 11:37:05 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "21sh.h"

/*
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
*/

int			exec_builtin(t_shell *shell, t_builtin builtin, t_ast *instr)
{
	int	ret;

	apply_redirs(shell, instr->data);
	set_pipeline(instr);
	ret = builtin(shell, ((t_command *)instr->data)->args);
	return (ret);
}
