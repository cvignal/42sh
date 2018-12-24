/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 16:24:09 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/24 17:49:27 by cvignal          ###   ########.fr       */
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

	i = shell->cursor;
	(void)shell;
	if (shell->cursor < ft_strlen(shell->line))
	{
		while (shell->line[i] != ' ' && i < ft_strlen(shell->line))
		{
			ft_rightkey(shell);
			i++;
		}
		ft_rightkey(shell);
	}
}

void	ft_prevword(t_shell *shell)
{
	size_t	i;

	i = shell->cursor;
	(void)shell;
	if (shell->cursor > 0)
	{
		while (shell->line[i] != ' ' && i > 0)
		{
			ft_leftkey(shell);
			i--;
		}
		ft_leftkey(shell);
		i--;
		while (shell->line[i] != ' ' && i > 0)
		{
			ft_leftkey(shell);
			i--;
		}
		if (shell->cursor > 0)
			ft_rightkey(shell);
	}
}
