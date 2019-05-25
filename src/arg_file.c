/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagrant </var/spool/mail/vagrant>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 21:34:02 by vagrant           #+#    #+#             */
/*   Updated: 2019/05/25 13:30:53 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "shell.h"
#include <unistd.h>
#include "fill_line.h"

int	read_from_file(t_shell *shell)
{
	char	*line;

	reset_terminal_mode(shell);
	shell->fd_op = 1;
	g_fd_output = 1;
	shell->ctrlc = 0;
	if (get_next_line(shell->arg_file->fd, &line) <= 0)
		return (1);
	shell->line.data = line;
	shell->line.len = ft_strlen(line);
	shell->history = NULL;
	return (0);
}
