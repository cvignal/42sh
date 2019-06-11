/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_leftkey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:54:44 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/11 11:05:10 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <term.h>
#include <curses.h>

#include "shell.h"
#include "fill_line.h"

int			vm_homekey(t_shell *shell)
{
	while (shell->line.cursor > 0)
		vm_leftkey(shell);
	return (0);
}

static int	vm_left_multi(t_shell *shell)
{
	t_curs			cursor;
	size_t			curs;

	curs = shell->line.cursor;
	get_cursor_pos(&cursor);
	if (cursor.col == 1)
		tputs(tgoto(tgetstr("cm", NULL), shell->win.ws_col - 1, cursor.line - 2)
				, 0, ft_printchar);
	else
		t_puts("le");
	if (shell->line.cursor <= shell->line.select_curs)
		ft_dprintf(shell->fd_op, "%s%c%s", INV_COLOR
			, shell->line.data[curs - 1], EOC);
	else
		ft_dprintf(shell->fd_op, "%c", shell->line.data[curs - 1]);
	if (cursor.col != 1)
		t_puts("le");
	shell->line.cursor--;
	return (0);
}

int			vm_leftkey(t_shell *shell)
{
	size_t	curs;

	curs = shell->line.cursor;
	if (curs == 0 || shell->line.data[curs - 1] == '\n')
		return (0);
	if (nb_multi_lines(shell, shell->line.len + 1, shell->prompt_len)
			&& shell->line.data[curs - 1] != '\n')
		return (vm_left_multi(shell));
	t_puts("le");
	shell->line.cursor--;
	if (shell->line.cursor <= shell->line.select_curs)
		ft_dprintf(shell->fd_op, "%s%c%s", INV_COLOR
				, shell->line.data[curs - 1], EOC);
	else
		ft_dprintf(shell->fd_op, "%c", shell->line.data[curs - 1]);
	t_puts("le");
	return (0);
}
