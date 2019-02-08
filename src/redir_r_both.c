/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_r_both.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 10:52:21 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/07 19:24:20 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "shell.h"

int	redir_r_both(t_shell *shell, t_ast *instr, t_redir *redir)
{
	int	fd;

	(void)shell;
	(void)instr;
	fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC,
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (1);
	redir->fd = fd;
	return (0);
}
