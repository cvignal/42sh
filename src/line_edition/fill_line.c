/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:41:08 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/13 15:26:27 by cvignal          ###   ########.fr       */
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

int		check_validity(t_shell *shell)
{
	char	*name;
	int		res;
	char	*default_term[3];

	if (!isatty(0))
		return (1);
	if (!(name = getenv("TERM")))
	{
		default_term[0] = "TERM";
		default_term[1] = "xterm-256color";
		set_env_var(shell, default_term[0], default_term[1]);
		name = default_term[1];
	}
	res = tgetent(NULL, name);
	if (res <= 0)
		return (1);
	raw_terminal_mode(shell);
	return (0);
}

void	raw_terminal_mode(t_shell *shell)
{
	struct termios term;

	(void)shell;
	if (tcgetattr(0, &term) == -1)
		return ;
	term.c_lflag &= ~(ICANON | ECHO | ISIG);
	term.c_lflag &= ~(OPOST);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return ;
	tgetent(NULL, getenv("TERM"));
}

void	reset_terminal_mode(t_shell *shell)
{
	struct termios term;

	(void)shell;
	if (tcgetattr(0, &term) == -1)
		return ;
	term.c_lflag |= (ICANON | ECHO | ISIG);
	term.c_lflag |= (OPOST);
	if (tcsetattr(0, TCSAFLUSH, &term) == -1)
		return ;
}

int		alt_fill_line(t_shell *shell)
{
	char *line;

	ft_dprintf(2, NOT_A_TTY);
	reset_terminal_mode(shell);
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

	if (check_validity(shell))
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
		ft_dprintf(shell->fd_op, "\n");
	shell->his_pos = -1;
	return (0);
}
