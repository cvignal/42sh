/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rightkey.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:46:06 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/12 20:40:11 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <stdlib.h>
#include <fcntl.h>
#include <curses.h>
#include <sys/ioctl.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

int			ft_rightkey(t_shell *shell)
{
	struct winsize	win;
	t_curs			*cursor;
	char			c;

	if (shell->line.cursor < shell->line.len)
	{
		c = shell->line.data[shell->line.cursor];
		shell->line.cursor++;
		if (shell->line.mode)
		{
			if (shell->line.cursor >= shell->line.select_curs)
				ft_dprintf(shell->fd_op, "%s%c%s", "\e[7;m", c, EOC);
			else
				ft_dprintf(shell->fd_op, "%c", c);
		}
		if (!(cursor = get_cursor_pos()))
			return (1);
		ioctl(0, TIOCGWINSZ, &win);
		tputs(tgetstr(win.ws_col == cursor->col ? "do" : "nd", NULL)
					, 0, ft_printchar);
		if (c == '\n')
			tputs(tgetstr("do", NULL), 0, ft_printchar);
		free(cursor);
	}
	return (0);
}
