/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_save_common.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 20:26:25 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/07 20:39:21 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"

int	redir_save_l(struct s_redir *, t_ast *instr)
{
	instr->old_fd[redir->in] = dup(STDIN_FILENO);
}

int	redir_save_ll(t_redir *redir, t_ast *instr)
{
	instr->old_fd[redir->in] = dup(STDIN_FILENO);
}

int redir_save_r(t_redir *redir, t_ast *instr)
{
	instr->old_fds[redir->out] = dup(STDIN_FILENO);
}

int redir_save_rr(t_redir *redir, t_ast *instr)
{
	instr->old_fds[redir->out] = dup(STDIN_FILENO);
}
