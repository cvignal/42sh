/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 11:43:49 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/21 14:29:23 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "minishell.h"
#include "libft.h"

int	apply_redirs(t_command *command)
{
	t_redir	*redir;

	redir = command->redir_list;
	while (redir)
	{
		if (redir->redir_act(redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	redir_l(t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_RDONLY);
	if (fd < 0)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redir_ll(t_redir *redir)
{
	t_heredoc	*heredoc;
	int			fd[2];

	if (!(heredoc = alloc_heredoc()))
		return (1);
	if (read_heredoc(heredoc, redir))
		return (heredoc_exit_error(heredoc));
	if (pipe(fd))
		return (heredoc_exit_error(heredoc));
	dup2(fd[0], STDIN_FILENO);
	write(fd[1], heredoc->data, heredoc->len);
	close(fd[0]);
	close(fd[1]);
	free(heredoc->data);
	free(heredoc);
	return (0);
}

int	redir_r(t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC,
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redir_rr(t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_CREAT | O_APPEND,
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
