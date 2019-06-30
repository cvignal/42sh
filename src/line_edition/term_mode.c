/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:01:19 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/28 08:51:36 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "shell.h"
#include "fill_line.h"

int		init_termios(t_shell *shell)
{
	struct termios term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (1);
	ft_memcpy(&shell->rst_term, &term, sizeof(term));
	term.c_lflag &= ~(ICANON | ECHO | ISIG);
	term.c_iflag &= ~(IXON | ICRNL);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	ft_memcpy(&shell->raw_term, &term, sizeof(term));
	return (0);
}

int		check_validity(t_shell *shell)
{
	char	*name;
	int		res;
	char	*default_term[3];

	if (shell->arg_file != NULL)
		return (2);
	if (!isatty(0))
		return (1);
	if (!(name = getenv("TERM")) || ft_strnequ(name, "dumb", 4))
	{
		default_term[0] = "TERM";
		default_term[1] = "xterm-256color";
		set_var(&shell->vars, default_term[0], default_term[1], 1);
		name = default_term[1];
	}
	res = tgetent(NULL, name);
	if (res <= 0)
		return (1);
	ioctl(0, TIOCGWINSZ, &shell->win);
	return (0);
}

int		raw_terminal_mode(t_shell *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &shell->raw_term) == -1)
		return (1);
	tgetent(NULL, getenv("TERM"));
	return (0);
}

int		reset_terminal_mode(t_shell *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &shell->rst_term) == -1)
		return (1);
	return (0);
}

