/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:47:09 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/12 11:12:46 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "shell.h"
#include "fill_line.h"
#include "libft.h"

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
	if ((fd_hf = open_history_file(shell)) == -1)
		return (1);
	while (get_next_line(fd_hf, &line) == 1)
	{
		if (ft_arrayadd(shell->history, line))
			return (1);
		free(line);
	}
	if (close(fd_hf) == -1)
		return (1);
	return (open_tty_fd(shell));
}

static int	add_complete_command(char *str, t_shell *shell
		, char **multi_line, int fd_hf)
{
	int	len;

	if (*multi_line && !shell->prev_cmd_state)
	{
		if (!(*multi_line = ft_strjoin_free(*multi_line, str, 1)))
			return (1);
		len = shell->history->length - 1;
		ft_strdel(&shell->history->data[len]);
		if (!(shell->history->data[len] = ft_strdup(*multi_line)))
			return (1);
		ft_dprintf(fd_hf, "%s\n", *multi_line);
		ft_strdel(multi_line);
		return (0);
	}
	if (ft_arrayadd(shell->history, str))
		return (1);
	ft_dprintf(fd_hf, "%s\n", str);
	if (*multi_line && shell->prev_cmd_state)
		ft_strdel(multi_line);
	shell->prev_cmd_state = 0;
	return (0);
}

static int	add_incomplete_command(char *str, t_shell *shell, char **multi_line)
{
	int	len;

	if (*multi_line)
	{
		if (!(*multi_line = ft_strjoin_free(*multi_line, str, 1)))
			return (1);
		if (!(*multi_line = ft_strjoin_free(*multi_line, "\n", 1)))
			return (1);
		len = shell->history->length - 1;
		ft_strdel(&shell->history->data[len]);
		if (!(shell->history->data[len] = ft_strdup(*multi_line)))
			return (1);
	}
	else
	{
		if (!(*multi_line = ft_strjoin_free(str, "\n", 0)))
			return (1);
		if (ft_arrayadd(shell->history, str))
			return (1);
	}
	return (0);
}

int			add_to_history(char *str, t_shell *shell, int flag)
{
	static char	*multi_line = NULL;
	int			fd_hf;
	int			ret;

	if (check_validity(shell))
		return (0);
	if (flag)
		return (add_incomplete_command(str, shell, &multi_line));
	else if (!flag && ft_strlen(str) && !ft_strnequ(str, "\033[", 2))
	{
		if ((fd_hf = open_history_file(shell)) == -1)
			return (1);
		ret = add_complete_command(str, shell, &multi_line, fd_hf);
		if (close(fd_hf) == -1)
			return (1);
		return (ret);
	}
	return (0);
}
