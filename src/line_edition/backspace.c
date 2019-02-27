/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backspace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:46:47 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/27 17:53:24 by cvignal          ###   ########.fr       */
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

	if (shell->line.cursor > 0)
	{
		shell->line.len--;
		curs = shell->line.cursor - 1;
		clear_cmd_line(shell);
		shell->line.cursor = 0;
		if (curs < shell->line.len)
			ft_del_char(shell->line.data, curs);
		else
			shell->line.data[shell->line.len] = 0;
		t_puts("sc");
		ft_dprintf(shell->fd_op, "%s", shell->line.data);
		t_puts("rc");
		while (shell->line.cursor < curs)
			ft_rightkey(shell);
	}
	return (0);
}
