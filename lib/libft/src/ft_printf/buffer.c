/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 05:01:09 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/21 18:12:09 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ft_printf.h"
#include "libft.h"

t_printf_buffer	*create_buffer(void)
{
	t_printf_buffer	*buffer;

	buffer = malloc(sizeof(*buffer));
	if (!buffer)
		return (NULL);
	buffer->data = malloc(sizeof(*buffer->data) * PRINTF_ALLOC_SIZE);
	if (!buffer->data)
	{
		free(buffer);
		return (NULL);
	}
	buffer->alloc_size = PRINTF_ALLOC_SIZE;
	buffer->pos = 0;
	buffer->error = 0;
	return (buffer);
}

int				add_to_buffer(t_printf_buffer *buffer, char c)
{
	if (buffer->error)
		return (1);
	if (buffer->pos % PRINTF_ALLOC_SIZE == 0)
	{
		buffer->data = ft_realloc(buffer->data, buffer->alloc_size,
				buffer->alloc_size + PRINTF_ALLOC_SIZE);
		if (!buffer->data)
		{
			buffer->error = 1;
			return (1);
		}
		buffer->alloc_size += PRINTF_ALLOC_SIZE;
	}
	buffer->data[buffer->pos++] = c;
	return (0);
}

int				add_to_buffer_nstring(t_printf_buffer *buffer,
		const char *s, size_t n)
{
	size_t		len;
	size_t		realloc_size;

	if (buffer->error)
		return (1);
	len = ft_strlen(s);
	if (buffer->pos + len >= buffer->alloc_size)
	{
		realloc_size = (len / PRINTF_ALLOC_SIZE) * PRINTF_ALLOC_SIZE;
		buffer->data = ft_realloc(buffer->data, buffer->alloc_size,
				buffer->alloc_size + realloc_size);
		if (!buffer->data)
		{
			buffer->error = 1;
			return (1);
		}
		buffer->alloc_size += realloc_size;
	}
	while (*s && n--)
		buffer->data[buffer->pos++] = *s++;
	return (0);
}

int				dump_buffer(int fd, t_printf_buffer *buffer)
{
	size_t		write_size;
	int			error;

	error = buffer->error;
	if (!error)
	{
		write_size = write(fd, buffer->data, buffer->pos);
		free(buffer->data);
	}
	free(buffer);
	return (error ? -1 : (int)write_size);
}

void			free_buffer(t_printf_buffer *buffer)
{
	if (!buffer->error)
		free(buffer->data);
	free(buffer);
}
