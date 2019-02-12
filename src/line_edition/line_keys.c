/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 19:02:11 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/12 15:32:04 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

static void	down_one_line(t_line line, int width, int flag)
{
	t_curs	*cursor;
	int		i;
	int		len_last_line;

	if (!(cursor = get_cursor_pos()))
		return ;
	tputs(tgoto(tgetstr("cm", NULL), cursor->col - 1, cursor->line)
			, 0, ft_printchar);
	len_last_line = line.len % width;
	if (flag)
		i = cursor->col - len_last_line - 4;
	else
		i = 0;
	while (i > 0)
	{
		tputs(tgetstr("le", NULL), 0, ft_printchar);
		i--;
	}
	free(cursor);
}

static void	back_to_startline(void)
{
	t_curs		*cursor;
	int			i;

	cursor = get_cursor_pos();
	i = cursor->col - 4;
	while (i < 0)
	{
		tputs(tgetstr("nd", NULL), 0, ft_printchar);
		i++;
	}
	free(cursor);
}

int			nb_multi_lines(size_t len)
{
	int				length;
	int				width;
	struct winsize	win;
	int				nb;

	length = (int)len;
	ioctl(0, TIOCGWINSZ, &win);
	width = win.ws_col;
	if (length + 3 >= width)
		length -= width - 3;
	else
		return (0);
	nb = 1;
	while ((length -= width) > 0)
		nb++;
	return (nb);
}

int			ft_lineup(t_shell *shell)
{
	int				cursor_nb;
	int				width;
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	width = win.ws_col;
	cursor_nb = nb_multi_lines(shell->line.cursor);
	if (cursor_nb > 0)
	{
		tputs(tgetstr("up", NULL), 0, ft_printchar);
		if (cursor_nb == 1)
			back_to_startline();
		if (shell->line.cursor < (size_t)width)
			shell->line.cursor = 0;
		else
			shell->line.cursor -= width;
	}
	return (0);
}

int			ft_linedown(t_shell *shell)
{
	int				line_nb;
	int				cursor_nb;
	int				width;
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	width = win.ws_col;
	line_nb = nb_multi_lines(shell->line.len);
	cursor_nb = nb_multi_lines(shell->line.cursor);
	if (cursor_nb < line_nb)
	{
		down_one_line(shell->line, width, (cursor_nb == line_nb - 1));
		shell->line.cursor += width;
		if (shell->line.cursor > shell->line.len)
			shell->line.cursor = shell->line.len;
	}
	return (0);
}
