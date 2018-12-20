/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 11:43:49 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/20 20:29:16 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "minishell.h"

int	apply_redirs(t_command *command, int is_builtin)
{
	t_redir	*redir;

	redir = command->redir_list;
	while (redir)
	{
		if (redir->redir_act(redir, is_builtin))
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	redir_l(t_redir *redir, int is_builtin)
{
	int	fd;

	if (is_builtin)
		redir->fd_copy[STDIN_FILENO] = dup(STDIN_FILENO);
	fd = open(redir->target, O_RDONLY);
	if (fd < 0)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redir_ll(t_redir *redir, int is_builtin)
{
	(void)redir;
	(void)is_builtin;
	return (0);
}

int	redir_r(t_redir *redir, int is_builtin)
{
	int	fd;

	if (is_builtin)
		redir->fd_copy[STDOUT_FILENO] = dup(STDOUT_FILENO);
	fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC,
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redir_rr(t_redir *redir, int is_builtin)
{
	int	fd;

	if (is_builtin)
		redir->fd_copy[STDOUT_FILENO] = dup(STDOUT_FILENO);
	fd = open(redir->target, O_CREAT | O_APPEND,
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
