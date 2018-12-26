/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 19:02:11 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/26 20:17:13 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "21sh.h"
#include "libft.h"
#include "fill_line.h"

void	ft_lineup(t_shell *shell)
{
	struct	winsize win;
	size_t	width;

	ioctl(0, TIOCGWINSZ, &win);
	width = win.ws_col;
	if (shell->line.cursor + 3 > width)
	{
		tputs(tgetstr("up", NULL), 0, ft_printchar);
		shell->line.cursor -= width;
	}
}

void	ft_linedown(t_shell *shell)
{
	struct	winsize win;
	size_t	width;

	ioctl(0, TIOCGWINSZ, &win);
	width = win.ws_col;
	if (shell->line.len + 3 > width && shell->line.cursor + 3 < width)
	{
		tputs(tgetstr("do", NULL), 0, ft_printchar);
		shell->line.cursor += width;
	}
}
