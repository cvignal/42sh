/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_insertion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 11:44:35 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/13 13:54:19 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "libft.h"
#include "shell.h"
#include "fill_line.h"

static void	print_multi_lines(t_shell *shell, char *buf)
{
	t_curs			*cursor;
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	t_puts("ce");
	if (!(cursor = get_cursor_pos()))
		return ;
	ft_dprintf(shell->fd_op, "%s", buf);
	t_puts("sc");
	ft_dprintf(shell->fd_op, "%s", shell->line.data + shell->line.cursor);
	t_puts("rc");
	if (cursor->col == win.ws_col)
		t_puts("do");
	free(cursor);
}

void		print_line(t_shell *shell, char *buf)
{
	t_curs			*cursor;
	struct winsize	win;

	cursor = NULL;
	ioctl(0, TIOCGWINSZ, &win);
	if (!nb_multi_lines(shell->line.len)
			&& shell->line.len == shell->line.cursor)
	{
		if (!(cursor = get_cursor_pos()))
			return ;
		t_puts("im");
		ft_dprintf(shell->fd_op, "%s", buf);
		t_puts("ei");
		if (cursor->col == win.ws_col)
			t_puts("do");
	}
	else
		print_multi_lines(shell, buf);
	if (cursor)
		free(cursor);
}
