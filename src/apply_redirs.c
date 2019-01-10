/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:01:29 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/08 10:14:39 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "ast.h"

int		apply_redirs(t_shell *shell, t_ast *instr)
{
	(void)shell;
	if (instr->fds[STDIN_FILENO] != STDIN_FILENO)
		dup2(instr->fds[STDIN_FILENO], STDIN_FILENO);
	if (instr->fds[STDOUT_FILENO] != STDOUT_FILENO)
		dup2(instr->fds[STDOUT_FILENO], STDOUT_FILENO);
	if (instr->fds[STDERR_FILENO] != STDERR_FILENO)
		dup2(instr->fds[STDOUT_FILENO], STDOUT_FILENO);
	return (0);
}
