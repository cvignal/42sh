/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 13:37:50 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/08 15:37:28 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>

#include "fill_line.h"
#include "libft.h"

int	ft_copy(t_shell *shell)
{
	unsigned int	begin;
	unsigned int	end;

	if (!shell->line.mode)
		return (0);
	if (shell->line.cursor > shell->line.select_curs)
	{
		begin = shell->line.select_curs;
		end = shell->line.cursor;
	}
	else
	{
		begin = shell->line.cursor;
		end = shell->line.select_curs;
	}
	if (shell->pbpaste)
		ft_strdel(&shell->pbpaste);
	shell->pbpaste = ft_strsub(shell->line.data, begin, end - begin);
	return (0);
}

int	ft_paste(t_shell *shell)
{
	if (shell->pbpaste && shell->line.mode)
		ft_addchar(shell, shell->pbpaste);
	return (0);
}

int	ft_cut(t_shell *shell)
{
	ft_copy(shell);
	if (shell->line.cursor > shell->line.select_curs)
	{
		shell->line.mode = 0;
		while (shell->line.cursor > shell->line.select_curs)
			ft_backspace(shell);
		shell->line.mode = 1;
	}
	return (0);
}

int	ft_switch_mode(t_shell *shell)
{
	if (shell->line.mode == 0)
	{
		shell->line.mode = 1;
		shell->line.select_curs = shell->line.cursor;
	}
	else
	{
		shell->line.mode = 0;
		tputs(tgetstr("dl", NULL), 0, ft_printchar);
		tputs(tgetstr("cr", NULL), 0, ft_printchar);
		ft_dprintf(g_fd_output, "$> %s", shell->line.data);
		shell->line.cursor = shell->line.len;
	}
	return (0);
}
