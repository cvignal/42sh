/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:46:07 by cvignal           #+#    #+#             */
/*   Updated: 2019/05/25 13:26:35 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "fill_line.h"

#include <unistd.h>

int	alt_fill_line(t_shell *shell)
{
	char	*line;

	reset_terminal_mode(shell);
	shell->fd_op = 1;
	g_fd_output = 1;
	shell->ctrlc = 0;
	if (get_next_line(0, &line) <= 0)
		return (1);
	shell->line.data = line;
	shell->line.len = ft_strlen(line);
	shell->history = NULL;
	return (0);
}

int	alt_init_shell(t_shell *shell)
{
	shell->history = NULL;
	shell->fd_op = 1;
	g_fd_output = 1;
	return (0);
}
