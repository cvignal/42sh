/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 10:26:43 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/07 21:16:31 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "21sh.h"

int	reset_redirs(t_ast *instr)
{
	t_redir	*redir;

	if (instr->left)
		reset_redirs(instr->left);
	redir = instr->redir_list;
	while (redir)
	{
		redir->reset(redir, instr);
		redir = redir->next;
	}
	if (instr->right)
		reset_redirs(instr->right);
	return (0);
}

int	redir_l_reset(t_redir *redir, t_ast *instr)
{
	(void)redir;
	dup2(instr->old_fds[STDIN_FILENO], STDIN_FILENO);
	close(instr->old_fds[STDIN_FILENO]);
	return (0);
}
