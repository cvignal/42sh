/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 16:24:09 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/02 13:09:15 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>

#include "fill_line.h"
#include "21sh.h"
#include "libft.h"

void	ft_nextword(t_shell *shell)
{
	size_t	i;

	i = shell->line.cursor;
	(void)shell;
	if (shell->line.cursor < shell->line.len)
	{
		while (shell->line.data[i] != ' ' && i < shell->line.len)
		{
			ft_rightkey(shell);
			i++;
		}
		while (shell->line.data[i] == ' ' && i < shell->line.len)
		{
			ft_rightkey(shell);
			i++;
		}
	}
}

void	ft_prevword(t_shell *shell)
{
	size_t	i;

	i = shell->line.cursor;
	(void)shell;
	if (shell->line.cursor > 0)
	{
		while (shell->line.data[i] != ' ' && i > 0)
		{
			ft_leftkey(shell);
			i--;
		}
		while (shell->line.data[i] == ' ' && i > 0)
		{
			ft_leftkey(shell);
			i--;
		}
		while (shell->line.data[i] != ' ' && i > 0)
		{
			ft_leftkey(shell);
			i--;
		}
		if (shell->line.cursor > 0)
			ft_rightkey(shell);
	}
}
