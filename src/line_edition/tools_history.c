/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:47:09 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/16 16:15:07 by cvignal          ###   ########.fr       */
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
	shell->his_pos = -1;
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
	t_list	*new;
	int		new_fd;

	shell->history = NULL;
	shell->output = NULL;
	shell->current = NULL;
	if ((shell->fd_hf = open(".shperso_history", O_RDWR | O_APPEND
					| O_CREAT, 0644)) == -1)
		return (1);
	new_fd = get_next_fd(shell);
	if (dup2(shell->fd_hf, new_fd) == -1)
		return (1);
	close(shell->fd_hf);
	if (add_fd(shell, new_fd, 0) == -1)
		return (1);
	shell->fd_hf = new_fd;
	while (get_next_line(shell->fd_hf, &line) == 1)
	{
		if (!(new = ft_lstnew(line, ft_strlen(line) + 1)))
			return (1);
		ft_lstadd(&shell->history, new);
		free(line);
	}
	return (open_tty_fd(shell));
}

static int	add_complete_command(char *str, t_shell *shell, char **multi_line)
{
	t_list	*new;

	if (*multi_line && !shell->prev_cmd_state)
	{
		if (!(*multi_line = ft_strjoin_free(*multi_line, str, 1)))
			return (1);
		free(shell->history->content);
		if (!(shell->history->content = ft_strdup(*multi_line)))
			return (1);
		shell->history->content_size = ft_strlen(*multi_line) + 1;
		ft_dprintf(shell->fd_hf, "%s\n", *multi_line);
		ft_strdel(multi_line);
		return (0);
	}
	if (!(new = ft_lstnew(str, ft_strlen(str) + 1)))
		return (1);
	ft_lstadd(&shell->history, new);
	ft_dprintf(shell->fd_hf, "%s\n", str);
	if (*multi_line && shell->prev_cmd_state)
		ft_strdel(multi_line);
	shell->prev_cmd_state = 0;
	return (0);
}

static int	add_incomplete_command(char *str, t_shell *shell, char **multi_line)
{
	t_list *new;

	if (*multi_line)
	{
		if (!(*multi_line = ft_strjoin_free(*multi_line, str, 1)))
			return (1);
		if (!(*multi_line = ft_strjoin_free(*multi_line, "\n", 1)))
			return (1);
		free(shell->history->content);
		if (!(shell->history->content = ft_strdup(*multi_line)))
			return (1);
		shell->history->content_size = ft_strlen(*multi_line) + 1;
	}
	else
	{
		if (!(*multi_line = ft_strjoin_free(str, "\n", 0)))
			return (1);
		if (!(new = ft_lstnew(str, ft_strlen(str) + 1)))
			return (1);
		ft_lstadd(&shell->history, new);
	}
	return (0);
}

int			add_to_history(char *str, t_shell *shell, int flag)
{
	static char	*multi_line = NULL;

	if (check_validity(shell))
		return (0);
	if (flag)
		return (add_incomplete_command(str, shell, &multi_line));
	else if (!flag && ft_strlen(str) && !ft_strnequ(str, "\033[", 2))
		return (add_complete_command(str, shell, &multi_line));
	return (0);
}
