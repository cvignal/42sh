/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:55:56 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/21 12:15:25 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <stdlib.h>
#include <fcntl.h>
#include <curses.h>
#include <sys/ioctl.h>

#include "minishell.h"
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
		res->cursor--;
		ft_del_char(res->str, res->cursor);
	}
}

void	ft_addchar(t_cmdline *res, char *buf)
{
	if (res->cursor == ft_strlen(res->str))
	{
		res->str = ft_strjoin_free(res->str, buf, 1);
		ft_printf("%s", buf);
	}
	else
	{
		tputs(tgetstr("im", NULL), 1, ft_printchar);
		ft_printf("%s", buf);
		res->str = ft_insert_free(res->str, buf, res->cursor, 1);
		tputs(tgetstr("ei", NULL), 1, ft_printchar);
	}
	res->cursor++;
}
