/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:55:56 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/23 18:48:55 by gchainet         ###   ########.fr       */
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

void	ft_leftkey(t_cmdline *res, t_shell *shell)
{
	(void)shell;
	if (res->cursor > 0)
	{
		tputs(tgetstr("le", NULL), 0, ft_printchar);
		res->cursor--;
	}
}

void	ft_rightkey(t_cmdline *res, t_shell *shell)
{
	(void)shell;
	if (res->cursor < ft_strlen(res->str))
	{
		tputs(tgetstr("nd", NULL), 0, ft_printchar);
		res->cursor++;
	}
}

void	ft_backspace(t_cmdline *res, t_shell *shell)
{
	(void)shell;
	if (res->cursor > 0)
	{
		tputs(tgetstr("le", NULL), 0, ft_printchar);
		tputs(tgetstr("dc", NULL), 0, ft_printchar);
		if (res->cursor < ft_strlen(res->str))
			ft_del_char(res->str, res->cursor - 1);
		else
			res->str[res->cursor - 1] = 0;
		res->cursor--;
	}
}

void	ft_homekey(t_cmdline *res, t_shell *shell)
{
	(void)shell;
	while (res->cursor > 0)
		ft_leftkey(res, shell);
}

void	ft_endkey(t_cmdline *res, t_shell *shell)
{
	(void)shell;
	while (res->cursor < ft_strlen(res->str))
		ft_rightkey(res, shell);
}
