/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:55:58 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/27 15:24:00 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "fill_line.h"

int	vm_copy(t_shell *shell)
{
	unsigned int	begin;
	unsigned int	end;

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
		return (-1);
	return (1);
}
