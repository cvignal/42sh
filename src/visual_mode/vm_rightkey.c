/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_rightkey.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:55:29 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/11 11:05:46 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "fill_line.h"

int	vm_endkey(t_shell *shell)
{
	while (shell->line.cursor < shell->line.len)
		vm_rightkey(shell);
	return (0);
}

int	vm_rightkey(t_shell *shell)
{
	char			c;
	int				curs_col;

	if (shell->line.cursor == shell->line.len
			|| shell->line.data[shell->line.cursor] == '\n')
		return (0);
	shell->line.cursor++;
	c = shell->line.data[shell->line.cursor - 1];
	curs_col = pos_cursor_col(shell, shell->win.ws_col, 0);
	if (shell->line.select_curs < shell->line.cursor)
		ft_dprintf(shell->fd_op, "%s%c%s", INV_COLOR, c, EOC);
	else
		ft_dprintf(shell->fd_op, "%c", c);
	if (curs_col == shell->win.ws_col)
		t_puts("do");
	return (0);
}
