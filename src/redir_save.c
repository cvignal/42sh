/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 20:15:02 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/07 21:49:28 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"

int	redir_save(t_redir *redir, t_ast *instr)
{
	t_redir	*iter;

	iter = instr->redir_list;
	while (iter)
	{
		iter->save(redir, instr);
		iter = iter->next;
	}
	return (0);
}

int	redir_l_save(t_redir *redir, t_ast *instr)
{
	(void)redir;
	instr->old_fds[STDIN_FILENO] = dup(instr->old_fds[STDIN_FILENO]);
	return (0);
}

int	redir_ll_save(t_redir *redir, t_ast *instr)
{
	(void)redir;
	instr->old_fds[STDIN_FILENO] = dup(instr->old_fds[STDIN_FILENO]);
	return (0);
}

int	redir_r_save(t_redir *redir, t_ast *instr)
{
	(void)redir;
	instr->old_fds[STDOUT_FILENO] = dup(instr->old_fds[STDOUT_FILENO]);
	return (0);
}

int	redir_rr_save(t_redir *redir, t_ast *instr)
{
	(void)redir;
	instr->old_fds[STDOUT_FILENO] = dup(instr->old_fds[STDOUT_FILENO]);
	return (0);
}
