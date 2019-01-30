/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:41:08 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/30 12:11:36 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <stdlib.h>
#include <fcntl.h>
#include <curses.h>
#include <sys/ioctl.h>

#include "shell.h"
#include "fill_line.h"
#include "libft.h"

int		check_validity(void)
{
	char	*name;
	int		res;

	if (!isatty(0))
		return (1);
	if (!(name = getenv("TERM")))
		return (1);
	res = tgetent(NULL, name);
	if (res <= 0)
		return (1);
	return (0);
}

void	raw_terminal_mode(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO | ISIG);
	term.c_lflag &= ~(OPOST);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
	tgetent(NULL, getenv("TERM"));
}

void	reset_terminal_mode(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ICANON | ECHO | ISIG);
	term.c_lflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

int		alt_fill_line(t_shell *shell)
{
	char *line;

	ft_printf(NOT_A_TTY);
	reset_terminal_mode();
	if (get_next_line(0, &line) <= 0)
		return (1);
	shell->line.data = line;
	shell->line.len = ft_strlen(line);
	return (0);
}

int		fill_line(t_shell *shell)
{
	char			buf[9];
	int				ret;

	if (check_validity())
		return (alt_fill_line(shell));
	while ((ret = read(STDIN_FILENO, buf, 8)) > 0)
	{
		buf[ret] = 0;
		if (ft_strchr(buf, '\n'))
			break ;
		if (is_a_special_key(buf))
		{
			if (apply_key(buf, shell))
				break ;
		}
		else if (shell->line.mode == 0)
			ft_addchar(shell, buf);
	}
	if (!shell->line.data)
		ft_addchar(shell, "");
	clean_under_line(shell);
	if (!shell->end_heredoc)
		ft_printf("\n");
	shell->his_pos = -1;
	return (0);
}
