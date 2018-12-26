/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 10:04:30 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/26 19:25:20 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "libft.h"

static int	realloc_line(t_line *line)
{
	char			*new_data;
	unsigned int	i;

	new_data = malloc(sizeof(*new_data)
			* (line->alloc_size + LINE_ALLOC_SIZE + 1));
	if (!new_data)
		return (1);
	i = 0;
	while (i < line->len)
	{
		new_data[i] = line->data[i];
		++i;
	}
	ft_bzero(new_data + i, line->alloc_size + LINE_ALLOC_SIZE - i + 1);
	free(line->data);
	line->data = new_data;
	line->alloc_size += LINE_ALLOC_SIZE;
	return (0);
}

void	free_line(t_line *line)
{
	if (line->data)
		free(line->data);
	ft_bzero(line, sizeof(*line));
}

int		add_to_line(t_line *line, char *s)
{
	size_t	add_len;

	add_len = ft_strlen(s);
	while (line->len + add_len + 1 >= line->alloc_size)
	{
		if (realloc_line(line))
			return (1);
	}
	ft_memmove(line->data + line->cursor + add_len, line->data + line->cursor,
			line->len - line->cursor);
	ft_strncpy(line->data + line->cursor, s, add_len);
	line->len += add_len;
	line->cursor += add_len;
	return (0);
}
