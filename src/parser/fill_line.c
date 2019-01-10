/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:41:08 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/07 10:56:58 by cvignal          ###   ########.fr       */
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

static void	check_validity(void)
{
	char	*name;
	int		res;

	if (!isatty(0))
	{
		ft_dprintf(2, "Not a tty\n");
		exit(0);
	}
	if (!(name = getenv("TERM")))
	{
		ft_dprintf(2, "Specify a terminal type with set TERM <whatyouwant>\n");
		exit(0);
	}
	res = tgetent(NULL, name);
	if (res < 0)
	{
		ft_dprintf(2, "Could not access the termcap data base\n");
		exit(0);
	}
	if (!res)
	{
		ft_dprintf(2, "Terminal type %s is not defined\n", name);
		exit(0);
	}
}

void		raw_terminal_mode(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_lflag &= ~(OPOST);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
	tgetent(NULL, getenv("TERM"));
}

void		reset_terminal_mode(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ICANON | ECHO);
	term.c_lflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
}

int			fill_line(t_shell *shell)
{
	char			buf[8];
	int				ret;

	check_validity();
	while ((ret = read(STDIN_FILENO, buf, 8)) > 0)
	{
		buf[ret] = 0;
		if (ft_strchr(buf, '\n'))
			break ;
		if (is_a_special_key(buf))
			apply_key(buf, shell);
		else if (shell->line.mode == 0)
			ft_addchar(shell, buf);
	}
	if (!shell->line.data)
		ft_addchar(shell, "");
	clean_under_line();
	ft_printf("\n");
	return (0);
}
