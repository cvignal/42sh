/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:16:57 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/12 08:15:35 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "get_next_line.h"
#include "libft.h"

static void			delete_buffer(t_gnl_buffer **buffers, t_gnl_buffer *del)
{
	t_gnl_buffer	*i;

	if (*buffers == del)
	{
		i = (*buffers)->next;
		free(del);
		*buffers = i;
	}
	else
	{
		i = *buffers;
		while (i->next && i->next != del)
			i = i->next;
		if (i->next)
		{
			if (i->next->next)
				i->next = i->next->next;
			free(del);
		}
	}
}

static int			get_return_value(int line_pos, t_gnl_buffer **buffers,
		t_gnl_buffer *current)
{
	if (current->read_size < 0)
		return (-1);
	else
	{
		if (line_pos)
			return (1);
		delete_buffer(buffers, current);
	}
	return (0);
}

static int			copy_char(char *line, t_gnl_buffer *buff, int *line_pos)
{
	if (buff->buffer[buff->buffer_pos] != '\n')
		line[(*line_pos)++] = buff->buffer[buff->buffer_pos++];
	if (buff->buffer[buff->buffer_pos] == '\n')
	{
		buff->buffer_pos++;
		return (1);
	}
	return (0);
}

static t_gnl_buffer	*get_current_buffer(const int fd, t_gnl_buffer **buffers)
{
	t_gnl_buffer	*current;
	t_gnl_buffer	*i;

	i = *buffers;
	while (i)
	{
		if (i->fd == fd)
			return (i);
		i = i->next;
	}
	current = malloc(sizeof(*current));
	if (!current)
		return (NULL);
	current->fd = fd;
	current->buffer_pos = 0;
	current->read_size = 0;
	current->next = *buffers;
	*buffers = current;
	return (current);
}

int					get_next_line(const int fd, char **line)
{
	static t_gnl_buffer	*buffers = NULL;
	t_gnl_buffer		*cb;
	int					line_pos;
	int					ac;

	line_pos = 0;
	ac = 0;
	if (!(cb = get_current_buffer(fd, &buffers)))
		return (-1);
	while (1)
	{
		if (cb->buffer_pos >= cb->read_size)
		{
			cb->buffer_pos = 0;
			if ((cb->read_size = read(fd, cb->buffer, BUFF_SIZE)) <= 0)
				return (get_return_value(line_pos, &buffers, cb));
		}
		if (line_pos % BUFF_SIZE == 0
				&& (!(*line = ft_realloc(*line, ac * BUFF_SIZE,
						(ac + 1) * BUFF_SIZE + 1)) || ++ac == 0))
			return (-1);
		if (copy_char(*line, cb, &line_pos))
			return (1);
	}
	return (0);
}
