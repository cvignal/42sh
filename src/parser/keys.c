/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:55:56 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/23 17:28:12 by cvignal          ###   ########.fr       */
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

static void	go_to_end_of_line(t_shell *shell)
{
	tputs(tgetstr("up", NULL), 0, ft_printchar);
}

void	ft_leftkey(t_shell *shell)
{
	unsigned int	curs;

	curs = shell->line.cursor;
	if (shell->line.cursor > 0)
	{
		tputs(tgetstr("le", NULL), 0, ft_printchar);
		shell->line.cursor--;
		if (shell->line.data[curs - 1] == '\n')
			go_to_end_of_line(shell);
		if (shell->line.mode)
		{
			if (shell->line.cursor <= shell->line.select_curs)
			{
				ft_printf("%s%c%s", "\e[7;m", shell->line.data[curs - 1], EOC);
				tputs(tgetstr("le", NULL), 0, ft_printchar);
			}
			else
				ft_printf("%c", shell->line.data[curs - 1]);
		}
	}
}

void	ft_rightkey(t_shell *shell)
{
	struct winsize	win;
	t_curs			*cursor;
	unsigned int	curs;

	curs = shell->line.cursor;
	ioctl(0, TIOCGWINSZ, &win);
	cursor = get_cursor_pos();
	if (shell->line.cursor < shell->line.len)
	{
		shell->line.cursor++;
		if (shell->line.mode)
		{
			if (shell->line.cursor >= shell->line.select_curs)
				ft_printf("%s%c%s", "\e[7;m", shell->line.data[curs], EOC);
			else
				ft_printf("%c", shell->line.data[curs]);
		}
		else
			tputs(tgetstr(win.ws_col == cursor->col ? "do" : "nd", NULL)
					, 0, ft_printchar);
	}
	free(cursor);
}

void	ft_backspace(t_shell *shell)
{
	struct winsize	win;
	t_curs			*cursor;

	ioctl(0, TIOCGWINSZ, &win);
	cursor = get_cursor_pos();
	if (shell->line.cursor > 0 && shell->line.mode == 0)
	{
		tputs(tgetstr("le", NULL), 0, ft_printchar);
		tputs(tgetstr("dc", NULL), 0, ft_printchar);
		if (cursor->col == win.ws_col)
			tputs(tgetstr("dc", NULL), 0, ft_printchar);
		if (shell->line.cursor < shell->line.len)
			ft_del_char(shell->line.data, shell->line.cursor - 1);
		else
			shell->line.data[shell->line.cursor - 1] = 0;
		shell->line.len--;
		shell->line.cursor--;
	}
	free(cursor);
}
