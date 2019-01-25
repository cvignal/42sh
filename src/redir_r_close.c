/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_r_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 19:41:37 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/25 14:46:34 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"

int	redir_r_close(t_shell *shell, t_ast *instr, t_redir *redir)
{
	(void)shell;
	instr->fds[redir->in] = -2;
	return (0);
}
