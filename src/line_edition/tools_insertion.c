/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_insertion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 11:44:35 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/12 15:45:26 by cvignal          ###   ########.fr       */
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
	tputs(tgetstr("ce", NULL), 0, ft_printchar);
	ft_dprintf(shell->fd_op, "%s", buf);
	tputs(tgetstr("sc", NULL), 0, ft_printchar);
	ft_dprintf(shell->fd_op, "%s", shell->line.data + shell->line.cursor);
	tputs(tgetstr("rc", NULL), 0, ft_printchar);
	if (!(cursor = get_cursor_pos()))
		return ;
	if (cursor->col - 1 == win.ws_col)
		tputs(tgetstr("do", NULL), 0, ft_printchar);
	free(cursor);
}

void	print_line(t_shell *shell, char *buf)
{
	t_curs			*cursor;
	struct winsize	win;

	cursor = NULL;
	ioctl(0, TIOCGWINSZ, &win);
	if (!nb_multi_lines(shell->line.len)
			|| shell->line.len == shell->line.cursor)
	{
		tputs(tgetstr("im", NULL), 0, ft_printchar);
		ft_dprintf(shell->fd_op, "%s", buf);
		tputs(tgetstr("ei", NULL), 0, ft_printchar);
		if (!(cursor = get_cursor_pos()))
			return ;
		if (cursor->col - 1 == win.ws_col)
			tputs(tgetstr("do", NULL), 0, ft_printchar);
	}
	else
		print_multi_lines(shell, buf);
	if (cursor)
		free(cursor);
}
