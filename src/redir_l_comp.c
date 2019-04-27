/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_l_comp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 11:16:49 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/27 19:02:11 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"

int	redir_l_comp(t_shell *shell, t_ast *instr, t_redir *redir)
{
	(void)shell;
	(void)instr;
	redir->fd = redir->out;
	return (0);
}
