/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backspace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:46:47 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/13 10:47:52 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <stdlib.h>
#include <fcntl.h>
#include <curses.h>
#include <sys/ioctl.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

int		ft_backspace(t_shell *shell)
{
	size_t	curs;

	if (shell->line.cursor > 0 && !shell->line.mode)
	{
		shell->line.len--;
		curs = shell->line.cursor - 1;
		while (shell->line.cursor)
			ft_leftkey(shell);
		t_puts("cd");
		t_puts("sc");
		if (curs < shell->line.len)
			ft_del_char(shell->line.data, curs);
		else
			shell->line.data[shell->line.len] = 0;
		ft_dprintf(shell->fd_op, "%s", shell->line.data);
		t_puts("rc");
		while (shell->line.cursor < curs)
			ft_rightkey(shell);
	}
	return (0);
}
