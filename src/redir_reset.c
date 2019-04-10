/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 10:26:43 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/01 10:46:52 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"

int	reset_redirs(t_shell *shell, t_ast *instr)
{
	t_redir			*redir;

	if (instr->left)
		reset_redirs(shell, instr->left);
	redir = instr->redir_list;
	while (redir)
	{
		if (redir->fd && redir->fd != STDOUT_FILENO
				&& redir->fd != STDIN_FILENO && redir->fd != STDERR_FILENO)
			close(redir->fd);
		redir = redir->next;
	}
	if (instr->right)
		reset_redirs(shell, instr->right);
	return (0);
}
