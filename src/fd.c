/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:06:18 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/08 16:26:17 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "shell.h"

int			get_next_fd(t_shell *shell)
{
	int		new_fd;
	t_fd	*iter;

	new_fd = 10;
	iter = shell->used_fd;
	while (iter && iter->fd == new_fd)
	{
		++new_fd;
		iter = iter->next;
	}
	return (new_fd);
}

int			add_fd(t_shell *shell, int fd, int is_pipe)
{
	t_fd	*new_fd;
	t_fd	*iter;

	new_fd = malloc(sizeof(*new_fd));
	if (!new_fd)
		return (-1);
	new_fd->fd = fd;
	new_fd->is_pipe = is_pipe;
	new_fd->next = NULL;
	iter = shell->used_fd;
	if (!iter || iter->fd > fd)
	{
		new_fd->next = iter;
		shell->used_fd = new_fd;
	}
	else
	{
		while (iter->next && iter->next->fd < fd)
			iter = iter->next;
		new_fd->next = iter->next;
		iter->next = new_fd;
	}
	return (fd);
}

void		remove_fd(t_shell *shell, int fd)
{
	t_fd	*iter;
	t_fd	*next;

	iter = shell->used_fd;
	if (iter)
	{
		if (iter->fd == fd)
		{
			next = iter->next;
			free(iter);
			shell->used_fd = next;
		}
		else
		{
			while (iter->next && iter->next->fd != fd)
				iter = iter->next;
			if (iter->next)
			{
				next = iter->next->next;
				free(iter->next);
				iter->next = next;
			}
		}
	}
}

void		close_everything(t_shell *shell)
{
	t_fd	*next;

	while (shell->used_fd)
	{
		next = shell->used_fd->next;
		if (shell->used_fd->fd != shell->fd_op)
		{
			close(shell->used_fd->fd);
			free(shell->used_fd);
		}
		shell->used_fd = next;
	}
}

int			open_file(t_shell *shell, const char *file, int mode, int perm)
{
	int	fd;
	int	new_fd;

	if (perm)
		fd = open(file, mode, perm);
	else
		fd = open(file, mode);
	if (fd < 0)
	{
		ft_dprintf(2, "%s: %s: unable to open file \n", EXEC_NAME, file);
		return (-1);
	}
	if (fd < 10)
	{
		new_fd = get_next_fd(shell);
		dup2(fd, new_fd);
		close(fd);
	}
	else
		new_fd = fd;
	return (add_fd(shell, new_fd, 0));
}
