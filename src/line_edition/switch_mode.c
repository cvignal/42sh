/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 13:37:50 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/19 13:15:18 by cvignal          ###   ########.fr       */
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
		end = shell->line.cursor + 1;
	}
	else
	{
		begin = shell->line.cursor;
		end = shell->line.select_curs + 1;
	}
	if (shell->pbpaste)
		ft_strdel(&shell->pbpaste);
	if (!(shell->pbpaste = ft_strsub(shell->line.data, begin, end - begin)))
		return (1);
	return (0);
}

int	ft_paste(t_shell *shell)
{
	if (shell->pbpaste && !shell->line.mode)
		ft_addchar(shell, shell->pbpaste, 0);
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
	else
	{
		shell->line.mode = 0;
		while (shell->line.cursor < shell->line.select_curs)
		{
			ft_delete(shell);
			shell->line.select_curs--;
		}
		shell->line.mode = 1;
	}
	ft_switch_mode(shell);
	return (0);
}

int	ft_switch_mode(t_shell *shell)
{
	if (shell->line.mode == 0)
	{
		shell->line.mode = 1;
		if (shell->line.cursor < shell->line.len)
		{
			ft_dprintf(shell->fd_op, "%s%c%s", INV_COLOR
				, shell->line.data[shell->line.cursor], EOC);
			t_puts("le");
		}
		shell->line.select_curs = shell->line.cursor;
	}
	else
	{
		shell->line.mode = 0;
		t_puts("dl");
		t_puts("cr");
		print_prompt(NULL, shell, 0);
		if (shell->line.data)
			ft_dprintf(g_fd_output, "%s", shell->line.data);
		shell->line.cursor = shell->line.len;
	}
	return (0);
}
