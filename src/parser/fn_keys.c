/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 16:24:09 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/23 18:49:56 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>

#include "fill_line.h"
#include "21sh.h"
#include "libft.h"

void	ft_nextword(t_cmdline *res, t_shell *shell)
{
	size_t	i;

	i = res->cursor;
	(void)shell;
	if (res->cursor < ft_strlen(res->str))
	{
		while (res->str[i] != ' ' && i < ft_strlen(res->str))
		{
			ft_rightkey(res, shell);
			i++;
		}
		ft_rightkey(res, shell);
	}
}

void	ft_prevword(t_cmdline *res, t_shell *shell)
{
	size_t	i;

	i = res->cursor;
	(void)shell;
	if (res->cursor > 0)
	{
		while (res->str[i] != ' ' && i > 0)
		{
			ft_leftkey(res, shell);
			i--;
		}
		ft_leftkey(res, shell);
		i--;
		while (res->str[i] != ' ' && i > 0)
		{
			ft_leftkey(res, shell);
			i--;
		}
		if (res->cursor > 0)
			ft_rightkey(res, shell);
	}
}
