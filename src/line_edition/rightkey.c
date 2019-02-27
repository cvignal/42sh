/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rightkey.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:46:06 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/27 17:11:46 by cvignal          ###   ########.fr       */
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
	int				curs_col;
	char			c;

	if (shell->line.cursor < shell->line.len)
	{
		c = shell->line.data[shell->line.cursor];
		shell->line.cursor++;
		ioctl(0, TIOCGWINSZ, &win);
		curs_col = pos_cursor_col(shell, win.ws_col, 0);
		t_puts(win.ws_col == curs_col ? "do" : "nd");
		if (c == '\n')
			t_puts("do");
	}
	return (0);
}
