/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_rw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 01:08:46 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/12 01:26:07 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "shell.h"

int	redir_rw(t_shell *shell, t_ast *ast, t_redir *redir)
{
	int	fd;

	(void)ast;
	fd = open_file(shell, redir->target, O_RDWR | O_CREAT,
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (1);
	redir->fd = fd;
	return (0);
}
