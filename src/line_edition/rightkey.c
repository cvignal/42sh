/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rightkey.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:46:06 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/11 10:48:35 by cvignal          ###   ########.fr       */
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
	int				curs_col;
	char			c;

	if (shell->line.cursor < shell->line.len)
	{
		c = shell->line.data[shell->line.cursor];
		shell->line.cursor++;
		curs_col = pos_cursor_col(shell, shell->win.ws_col, 0);
		t_puts(shell->win.ws_col == curs_col ? "do" : "nd");
		if (c == '\n')
			t_puts("do");
	}
	return (0);
}
