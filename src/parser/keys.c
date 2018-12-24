/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:55:56 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/24 17:45:19 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <stdlib.h>
#include <fcntl.h>
#include <curses.h>
#include <sys/ioctl.h>

#include "21sh.h"
#include "libft.h"
#include "fill_line.h"

void	ft_leftkey(t_shell *shell)
{
	if (shell->cursor > 0)
	{
		tputs(tgetstr("le", NULL), 0, ft_printchar);
		shell->cursor--;
	}
}

void	ft_rightkey(t_shell *shell)
{
	if (shell->cursor < ft_strlen(shell->line))
	{
		tputs(tgetstr("nd", NULL), 0, ft_printchar);
		shell->cursor++;
	}
}

void	ft_backspace(t_shell *shell)
{
	if (shell->cursor > 0)
	{
		tputs(tgetstr("le", NULL), 0, ft_printchar);
		tputs(tgetstr("dc", NULL), 0, ft_printchar);
		if (shell->cursor < ft_strlen(shell->line))
			ft_del_char(shell->line, shell->cursor - 1);
		else
			shell->line[shell->cursor - 1] = 0;
		shell->cursor--;
	}
}

void	ft_homekey(t_shell *shell)
{
	while (shell->cursor > 0)
		ft_leftkey(shell);
}

void	ft_endkey(t_shell *shell)
{
	while (shell->cursor < ft_strlen(shell->line))
		ft_rightkey(shell);
}
