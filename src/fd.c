/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:06:18 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/25 17:29:32 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "shell.h"

static int	get_next_fd(t_shell *shell)
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

int			add_fd(t_shell *shell, int fd)
{
	t_fd	*new_fd;
	t_fd	*iter;

	new_fd = malloc(sizeof(*new_fd));
	if (!new_fd)
		return (-1);
	new_fd->fd = fd;
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
	return (add_fd(shell, new_fd));
}
