/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:35:51 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/11 19:22:53 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "shell.h"
#include "fill_line.h"

int			presence_of_date(char *str)
{
	int	i;

	i = 0;
	while (str[i] && i < 10)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (str[i] == ':');
}

static int	open_tty_fd(t_shell *shell)
{
	int	new_fd;

	shell->prev_cmd_state = 0;
	shell->his_pos = shell->history->length;
	shell->ctrld = 0;
	shell->end_heredoc = 0;
	raw_terminal_mode(shell);
	new_fd = get_next_fd(shell);
	if ((shell->fd_op = open(ttyname(0), O_WRONLY)) < 0)
		return (1);
	if (dup2(shell->fd_op, new_fd) == -1)
		return (1);
	if (close(shell->fd_op) == -1)
		return (1);
	if (add_fd(shell, new_fd, 0) == -1)
		return (1);
	shell->fd_op = new_fd;
	g_fd_output = new_fd;
	shell->pbpaste = NULL;
	return (0);
}

int			load_history(t_shell *shell)
{
	char	*line;
	int		fd_hf;

	if (!(shell->history = (t_array*)malloc(sizeof(t_array))))
		return (1);
	ft_bzero(shell->history, sizeof(t_array));
	shell->output = NULL;
	shell->current = NULL;
	if ((fd_hf = open(".shperso_history", O_RDWR | O_APPEND
					| O_CREAT, 0644)) == -1)
		return (1);
	while (get_next_line(fd_hf, &line) == 1)
	{
		if (ft_arrayadd(shell->history, line + 11 * presence_of_date(line)))
			return (1);
		free(line);
	}
	if (close(fd_hf) == -1)
		return (1);
	return (open_tty_fd(shell));
}
