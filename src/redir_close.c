/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:43:45 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/28 18:04:03 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"

int	redir_close(t_shell *shell, t_ast *instr, t_redir *redir)
{
	(void)shell;
	(void)instr;
	redir->fd = redir->in;
	return (0);
}
