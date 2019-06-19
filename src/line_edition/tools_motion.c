/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_motion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:28:55 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/12 15:46:10 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "libft.h"
#include "fill_line.h"
#include "shell.h"

size_t	length_prev_line(t_shell *shell)
{
	size_t	ret;
	size_t	j;
	int		k;

	j = 0;
	ret = 0;
	k = 0;
	while (shell->line.cursor > 0 && j < shell->line.cursor - 1)
	{
		j++;
		ret++;
		if (shell->line.data[j] == '\n')
		{
			ret = 0;
			k++;
		}
		else if ((j + shell->prompt_len) % shell->win.ws_col == 0)
		{
			ret = 1;
			k++;
		}
	}
	if (!k)
		ret += shell->prompt_len + 1;
	return (ret);
}

void	clean_under_line(t_shell *shell)
{
	t_curs			curs;
	struct winsize	win;

	t_puts("sc");
	if (shell)
	{
		while (shell->line.cursor < shell->line.len)
			ft_rightkey(shell);
	}
	else
	{
		ioctl(0, TIOCGWINSZ, &win);
		get_cursor_pos(&curs);
		if (curs.line != win.ws_row)
			t_puts("do");
	}
	t_puts("cd");
	if (!shell)
		t_puts("rc");
}
