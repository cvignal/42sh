/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_r_comp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 12:35:46 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 20:26:39 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "21sh.h"

int	redir_r_comp(t_shell *shell, t_ast *instr, t_redir *redir)
{
	(void)shell;
	instr->fds[redir->in] = redir->out;
	return (0);
}
