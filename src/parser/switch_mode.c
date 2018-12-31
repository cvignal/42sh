/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 13:37:50 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/31 15:54:27 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>

#include "fill_line.h"
#include "libft.h"

void	ft_copy(t_shell *shell)
{
	unsigned int	begin;
	unsigned int	end;

	if (!shell->line.mode)
		return ;
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
}

void	ft_paste(t_shell *shell)
{
	if (shell->pbpaste && shell->line.mode)
		ft_addchar(shell, shell->pbpaste);
}

void	ft_cut(t_shell *shell)
{
	ft_copy(shell);
	if (shell->line.cursor > shell->line.select_curs)
	{
		shell->line.mode = 0;
		while (shell->line.cursor > shell->line.select_curs)
			ft_backspace(shell);
		shell->line.mode = 1;
	}
}

void	ft_switch_mode(t_shell *shell)
{
	if (shell->line.mode == 0)
	{
		shell->line.mode = 1;
		shell->line.select_curs = shell->line.cursor;
	}
	else
		shell->line.mode = 0;
}
