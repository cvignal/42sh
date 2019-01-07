/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:01:29 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/07 20:14:46 by gchainet         ###   ########.fr       */
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
