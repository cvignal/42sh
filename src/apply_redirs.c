/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:01:29 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 20:40:47 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "21sh.h"
#include "ast.h"

int		apply_redirs(t_shell *shell, t_ast *instr)
{
	(void)shell;
	if (instr->fds[STDIN_FILENO] != STDIN_FILENO)
	{
		dup2(instr->fds[STDIN_FILENO], STDIN_FILENO);
		close(instr->fds[STDIN_FILENO]);
	}
	if (instr->fds[STDOUT_FILENO] != STDOUT_FILENO)
	{
		dup2(instr->fds[STDOUT_FILENO], STDOUT_FILENO);
		close(instr->fds[STDOUT_FILENO]);
	}
	if (instr->fds[STDERR_FILENO] != STDERR_FILENO)
	{
		dup2(instr->fds[STDOUT_FILENO], STDOUT_FILENO);
		close(instr->fds[STDOUT_FILENO]);
	}
	return (0);
}

int		reset_redirs(t_ast *instr)
{
	if (instr)
	{
		reset_redirs(instr->left);
		if (instr->fds[STDIN_FILENO] != STDIN_FILENO)
		{
			dup2(instr->old_fds[STDIN_FILENO], STDIN_FILENO);
			close(instr->old_fds[STDIN_FILENO]);
			close(instr->fds[STDIN_FILENO]);
		}
		if (instr->fds[STDOUT_FILENO] != STDOUT_FILENO)
		{
			dup2(instr->old_fds[STDOUT_FILENO], STDOUT_FILENO);
			close(instr->old_fds[STDOUT_FILENO]);
			close(instr->fds[STDOUT_FILENO]);
		}
		if (instr->fds[STDERR_FILENO] != STDERR_FILENO)
		{
			dup2(instr->old_fds[STDERR_FILENO], STDERR_FILENO);
			close(instr->old_fds[STDERR_FILENO]);
			close(instr->fds[STDERR_FILENO]);
		}
		reset_redirs(instr->right);
	}
	return (0);
}
