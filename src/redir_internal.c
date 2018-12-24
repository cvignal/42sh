/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 11:43:49 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/24 12:11:11 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "21sh.h"
#include "libft.h"

int	apply_redirs(t_shell *shell, t_command *command)
{
	t_redir	*redir;

	redir = command->redir_list;
	while (redir)
	{
		if (redir->redir_act(shell, redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	redir_l(t_shell *shell, t_redir *redir)
{
	int	fd;

	(void)shell;
	fd = open(redir->target, O_RDONLY);
	if (fd < 0)
		return (1);
	dup2(fd, redir->in);
	close(fd);
	return (0);
}

int	redir_ll(t_shell *shell, t_redir *redir)
{
	t_heredoc	*heredoc;
	int			fd[2];

	if (!(heredoc = alloc_heredoc()))
		return (1);
	if (read_heredoc(shell, heredoc, redir))
		return (heredoc_exit_error(heredoc));
	if (pipe(fd))
		return (heredoc_exit_error(heredoc));
	dup2(fd[0], redir->in);
	write(fd[1], heredoc->data, heredoc->len);
	close(fd[0]);
	close(fd[1]);
	free(heredoc->data);
	free(heredoc);
	return (0);
}

int	redir_r(t_shell *shell, t_redir *redir)
{
	int	fd;

	(void)shell;
	fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC,
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (1);
	dup2(fd, redir->in);
	close(fd);
	return (0);
}

int	redir_rr(t_shell *shell, t_redir *redir)
{
	int	fd;

	(void)shell;
	fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND,
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (1);
	dup2(fd, redir->in);
	close(fd);
	return (0);
}
