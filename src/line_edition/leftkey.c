/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leftkey.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:48:22 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/12 21:37:54 by gchainet         ###   ########.fr       */
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

void		go_to_end_of_line(t_shell *shell)
{
	size_t	len;

	tputs(tgetstr("up", NULL), 0, ft_printchar);
	if (shell->line.cursor > 0 &&
			shell->line.data[shell->line.cursor - 1] == '\n')
		return ;
	len = length_prev_line(shell);
	while (len > 0)
	{
		tputs(tgetstr("nd", NULL), 0, ft_printchar);
		len--;
	}
}

static void	left_key_multi(t_shell *shell)
{
	t_curs			*cursor;
	struct winsize	win;

	if (!(cursor = get_cursor_pos()))
		return ;
	ioctl(0, TIOCGWINSZ, &win);
	if (cursor->col == 1)
		tputs(tgoto(tgetstr("cm", NULL), win.ws_col - 1, cursor->line - 2)
			, 0, ft_printchar);
	else
		tputs(tgetstr("le", NULL), 0, ft_printchar);
	shell->line.cursor--;
}

int			ft_leftkey(t_shell *shell)
{
	unsigned int	curs;

	curs = shell->line.cursor;
	if (shell->line.cursor > 0)
	{
		if (nb_multi_lines(shell->line.len + 1))
			left_key_multi(shell);
		else
		{
			tputs(tgetstr("le", NULL), 0, ft_printchar);
			shell->line.cursor--;
		}
		if (shell->line.data[curs - 1] == '\n')
			go_to_end_of_line(shell);
		if (shell->line.mode)
		{
			if (shell->line.cursor < shell->line.select_curs)
				ft_dprintf(shell->fd_op, "%s%c%s", "\e[7;m"
						, shell->line.data[curs - 1], EOC);
			else
				ft_dprintf(shell->fd_op, "%c", shell->line.data[curs - 1]);
			tputs(tgetstr("le", NULL), 0, ft_printchar);
		}
	}
	return (0);
}
