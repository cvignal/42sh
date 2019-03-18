/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 10:26:43 by gchainet          #+#    #+#             */
/*   Updated: 2019/03/18 11:19:08 by cvignal          ###   ########.fr       */
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
		close(redir->fd);
		redir = redir->next;
	}
	if (instr->right)
		reset_redirs(shell, instr->right);
	return (0);
}
