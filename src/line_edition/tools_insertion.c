/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_insertion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 11:44:35 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/24 22:15:39 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "shell.h"
#include "fill_line.h"

void		print_line_bis(t_shell *shell)
{
	char	*str;
	size_t	i;

	str = shell->line.data;
	if (!ft_strchr(str, '\t') && !ft_strchr(str, '\r'))
		ft_dprintf(shell->fd_op, "%s", str);
	else
	{
		i = 0;
		while (str[i])
		{
			ft_dprintf(shell->fd_op, "%c", (str[i] != 13 && str[i] != '\t')
					? str[i] : '?');
			i++;
		}
	}
}

int			pos_in_special_line(t_shell *shell)
{
	int	ret;
	int	i;
	int	k;

	i = 0;
	ret = 0;
	k = 0;
	while (i < (int)shell->line.cursor)
	{
		if (shell->line.data[i] == '\n')
		{
			ret = 0;
			k = 1;
		}
		else
			ret++;
		i++;
	}
	if (!k)
		ret += shell->prompt_len;
	return (ret);
}

int			pos_cursor_col(t_shell *shell, int width, int len)
{
	int	ret;
	int	length;

	if (!nb_multi_lines(shell, shell->line.cursor - len, shell->prompt_len))
		ret = shell->prompt_len + shell->line.cursor;
	else
	{
		if (ft_strnchr(shell->line.data, '\n', shell->line.cursor))
			return (pos_in_special_line(shell));
		length = (int)shell->line.cursor;
		length -= width - shell->prompt_len;
		ret = length % width;
	}
	if (ret <= 0)
		ret = width;
	return (ret);
}

static void	print_multi_lines(t_shell *shell, char buf)
{
	int	curs_col;

	t_puts("ce");
	curs_col = pos_cursor_col(shell, shell->win.ws_col, 1);
	ft_dprintf(shell->fd_op, "%c", (buf != 13 && buf != '\t') ? buf : '?');
	t_puts("sc");
	ft_dprintf(shell->fd_op, "%s", shell->line.data + shell->line.cursor);
	t_puts("rc");
	if (curs_col == shell->win.ws_col)
		t_puts("do");
}

void		print_line(t_shell *shell, char buf)
{
	int				curs_col;

	if (!nb_multi_lines(shell, shell->line.len, shell->prompt_len)
			|| shell->line.len == shell->line.cursor)
	{
		curs_col = pos_cursor_col(shell, shell->win.ws_col, 1);
		t_puts("im");
		ft_dprintf(shell->fd_op, "%c", (buf != 13 && buf != '\t') ? buf : '?');
		t_puts("ei");
		if (curs_col == shell->win.ws_col)
			t_puts("do");
	}
	else
		print_multi_lines(shell, buf);
}
