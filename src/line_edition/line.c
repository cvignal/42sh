/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 08:40:13 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/11 21:47:28 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

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
	if (line->data)
		free(line->data);
	line->data = new_data;
	line->alloc_size += LINE_ALLOC_SIZE;
	return (0);
}

void		free_line(t_line *line)
{
	if (line->data)
		free(line->data);
	ft_bzero(line, sizeof(*line));
}

static void	reprint_line(t_line *line)
{
	t_curs			*cursor;
	struct winsize	win;

	cursor = get_cursor_pos();
	ioctl(0, TIOCGWINSZ, &win);
	tputs(tgetstr("sc", NULL), 0, ft_printchar);
	if (cursor->col != win.ws_col)
		tputs(tgetstr("ce", NULL), 0, ft_printchar);
	tputs(tgetstr("do", NULL), 0, ft_printchar);
	tputs(tgetstr("cd", NULL), 0, ft_printchar);
	tputs(tgetstr("rc", NULL), 0, ft_printchar);
	if (cursor->col == win.ws_col)
		tputs(tgetstr("nd", NULL), 0, ft_printchar);
	ft_dprintf(g_fd_output, "%s", line->data + line->cursor);
	tputs(tgetstr("rc", NULL), 0, ft_printchar);
}

int			add_to_line(t_line *line, char *s)
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
	tputs(tgetstr("im", NULL), 0, ft_printchar);
	ft_dprintf(g_fd_output, "%s", s);
	if (nb_multi_lines(line->len) != nb_multi_lines(line->cursor))
		reprint_line(line);
	tputs(tgetstr("ei", NULL), 0, ft_printchar);
	return (0);
}
