/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 10:40:01 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/11 20:02:46 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_read_fd(int fd, int *ret)
{
	char buf[BUFF_SIZE + 1];

	*ret = read(fd, buf, BUFF_SIZE);
	buf[*ret] = '\0';
	return (buf[0] == '\0' ? NULL : ft_strdup(buf));
}

static int		ft_pop_file(t_line **all_files, t_line *elem, int ret)
{
	t_line *curr;

	curr = *all_files;
	if (curr == elem)
	{
		free(elem);
	}
	else
	{
		while (curr)
		{
			if (curr->next == elem)
			{
				curr->next = elem->next;
				free(elem);
			}
			curr = curr->next;
		}
	}
	return (ret);
}

static int		ft_fill_line(t_line **all_files, t_line *elem, char **line)
{
	int		ret;
	char	*tmp;
	char	*buf;

	ret = 1;
	buf = (elem->file) ? elem->file : ft_read_fd(elem->fd, &ret);
	if (ret <= 0 || !(*line = ft_strdup("\0")))
		return (!*line ? -1 : ft_pop_file(all_files, elem, ret));
	while (ret > 0)
	{
		if ((tmp = ft_strchr(buf, '\n')))
		{
			*tmp = '\0';
			elem->file = ft_strdup(tmp + 1);
			if (!(*line = ft_strjoin_free(*line, buf, 3)))
				return (-1);
			return (1);
		}
		if (!(*line = ft_strjoin_free(*line, buf, 3)))
			return (-1);
		buf = ft_read_fd(elem->fd, &ret);
	}
	elem->file = NULL;
	return ((ft_strlen(*line) ? 1 : ret));
}

t_line static	*ft_new_file(int fd)
{
	t_line	*new_file;

	if (!(new_file = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	new_file->fd = fd;
	new_file->file = NULL;
	new_file->next = NULL;
	return (new_file);
}

int				get_next_line(const int fd, char **line)
{
	static t_line	*all_files = NULL;
	t_line			*curr;

	if (BUFF_SIZE < 1 || !line || fd < 0)
		return (-1);
	if (all_files)
	{
		curr = all_files;
		while (fd != curr->fd && curr->next)
			curr = curr->next;
		if (fd != curr->fd)
		{
			if (!(curr->next = ft_new_file(fd)))
				return (-1);
			curr = curr->next;
		}
	}
	else
	{
		if (!(all_files = ft_new_file(fd)))
			return (-1);
		curr = all_files;
	}
	return (ft_fill_line(&all_files, curr, line));
}
