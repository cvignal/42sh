/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 08:40:13 by gchainet          #+#    #+#             */
/*   Updated: 2019/03/11 21:00:45 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "libft.h"

static int	realloc_line(t_line *line)
{
	char			*new_data;
	unsigned int	i;

	if (!(new_data = ft_strnew(line->alloc_size + LINE_ALLOC_SIZE)))
		return (1);
	i = 0;
	while (i < line->len)
	{
		new_data[i] = line->data[i];
		++i;
	}
	ft_bzero(new_data + i, line->alloc_size + LINE_ALLOC_SIZE - i + 1);
	if (line->data)
		free(line->data);
	line->data = new_data;
	line->alloc_size += LINE_ALLOC_SIZE;
	return (0);
}

int			free_line(t_line *line)
{
	if (line->data)
		free(line->data);
	ft_bzero(line, sizeof(*line));
	return (1);
}

int			add_to_line(t_line *line, char buf)
{
	size_t	add_len;
	char	s[2];

	add_len = 1;
	while (line->len + add_len + 1 >= line->alloc_size)
	{
		if (realloc_line(line))
			return (1);
	}
	ft_memmove(line->data + line->cursor + add_len, line->data + line->cursor,
			line->len - line->cursor);
	s[0] = buf;
	s[1] = 0;
	ft_strncpy(line->data + line->cursor, s, add_len);
	line->len += add_len;
	line->cursor += add_len;
	return (0);
}
