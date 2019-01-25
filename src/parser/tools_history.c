/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:47:09 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/25 14:18:44 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "shell.h"
#include "fill_line.h"
#include "libft.h"

int			load_history(t_shell *shell)
{
	char	*line;
	t_list	*new;

	if ((shell->fd = open(".shperso_history", O_RDWR | O_APPEND
					| O_CREAT, 0644)) == -1)
		return (0);
	while (get_next_line(shell->fd, &line) == 1)
	{
		new = ft_lstnew(line, ft_strlen(line) + 1);
		ft_lstadd(&shell->history, new);
		free(line);
	}
	return (1);
}

static int	add_complete_command(char *str, t_shell *shell, char **multi_line)
{
	t_list	*new;

	if (*multi_line)
	{
		if (!(*multi_line = ft_strjoin_free(*multi_line, str, 1)))
			return (1);
		free(shell->history->content);
		if (!(shell->history->content = ft_strdup(*multi_line)))
			return (1);
		shell->history->content_size = ft_strlen(*multi_line) + 1;
		ft_dprintf(shell->fd, "%s\n", *multi_line);
		ft_strdel(multi_line);
		return (0);
	}
	if (!(new = ft_lstnew(str, ft_strlen(str) + 1)))
		return (1);
	ft_lstadd(&shell->history, new);
	ft_dprintf(shell->fd, "%s\n", str);
	return (0);
}

int			add_to_history(char *str, t_shell *shell, int flag)
{
	t_list		*new;
	static char	*multi_line = NULL;

	if (flag && multi_line)
	{
		if (!(multi_line = ft_strjoin_free(multi_line, str, 1)))
			return (1);
		if (!(multi_line = ft_strjoin_free(multi_line, "\n", 1)))
			return (1);
		free(shell->history->content);
		if (!(shell->history->content = ft_strdup(multi_line)))
			return (1);
		shell->history->content_size = ft_strlen(multi_line) + 1;
	}
	else if (flag && !multi_line)
	{
		if (!(multi_line = ft_strjoin_free(str, "\n", 0)))
			return (1);
		if (!(new = ft_lstnew(str, ft_strlen(str) + 1)))
			return (1);
		ft_lstadd(&shell->history, new);
	}
	else if (!flag && ft_strlen(str))
		return (add_complete_command(str, shell, &multi_line));
	return (0);
}
