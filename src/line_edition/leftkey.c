/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leftkey.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:48:22 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/12 17:43:18 by cvignal          ###   ########.fr       */
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

	t_puts("up");
	if (shell->line.cursor > 0
			&& shell->line.data[shell->line.cursor - 1] == '\n')
		return ;
	len = length_prev_line(shell);
	while (len > 0)
	{
		t_puts("nd");
		len--;
	}
}

static void	left_key_multi(t_shell *shell)
{
	t_curs			cursor;
	struct winsize	win;

	(void)shell;
	get_cursor_pos(&cursor);
	ioctl(0, TIOCGWINSZ, &win);
	if (cursor.col == 1)
		tputs(tgoto(tgetstr("cm", NULL), win.ws_col - 1, cursor.line - 2)
				, 0, ft_printchar);
	else
		t_puts("le");
}

int			ft_leftkey(t_shell *shell)
{
	unsigned int	curs;

	curs = shell->line.cursor;
	if (shell->line.cursor > 0)
	{
		if (nb_multi_lines(shell->line.len + 1, shell->prompt_len)
				&& shell->line.data[curs - 1] != '\n')
			left_key_multi(shell);
		else
			t_puts("le");
		shell->line.cursor--;
		if (shell->line.data[curs - 1] == '\n')
			go_to_end_of_line(shell);
	}
	return (0);
}
