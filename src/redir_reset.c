/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 10:26:43 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/07 10:32:45 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "21sh.h"

int	reset_redir_l(t_redir *redir, t_ast *instr)
{
	dup2(instr->old_fd[redir->in], STDIN_FILENO);
	close(instr->old_fd[redir->in]);
}
