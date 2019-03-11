/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:41:08 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/11 15:36:54 by cvignal          ###   ########.fr       */
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

int		g_fd_output;

int		check_validity(t_shell *shell)
{
	char	*name;
	int		res;
	char	*default_term[3];

	if (!isatty(0))
		return (1);
	if (!(name = getenv("TERM")) || ft_strnequ(name, "dumb", 4))
	{
		default_term[0] = "TERM";
		default_term[1] = "xterm-256color";
		set_env_var(shell, default_term[0], default_term[1]);
		name = default_term[1];
	}
	res = tgetent(NULL, name);
	if (res <= 0)
		return (1);
	shell->ctrlc = 0;
	return (0);
}

void	raw_terminal_mode(t_shell *shell)
{
	struct termios term;

	(void)shell;
	if (tcgetattr(0, &term) == -1)
		return ;
	term.c_lflag &= ~(ICANON | ECHO | ISIG | ECHOCTL);
	term.c_iflag &= ~(IXON | ICRNL);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return ;
	tgetent(NULL, getenv("TERM"));
}

void	reset_terminal_mode(t_shell *shell)
{
	struct termios term;

	(void)shell;
	if (tcgetattr(0, &term) == -1)
		return ;
	term.c_lflag |= (ICANON | ECHO | ISIG | ECHOCTL);
	term.c_iflag |= (IXON | ICRNL);
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return ;
}

int		fill_line(t_shell *shell)
{
	char			buf[9];
	int				ret;
	int				res;

	res = 0;
	if (shell->history)
		shell->his_pos = shell->history->length;
	while (!res && (ret = read(0, buf, 8)) > 0)
	{
		buf[ret] = 0;
		if (is_a_special_key(buf))
		{
			if (apply_key(buf, shell))
				break ;
		}
		else
			res = ft_addchar(shell, buf, 0);
	}
	if (!shell->line.alloc_size)
		shell->line.data = ft_strdup("");
	clean_under_line(shell);
	if (!shell->end_heredoc)
		ft_dprintf(shell->fd_op, "\n");
	return (res == -1 || shell->line.data == NULL);
}
