/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:47:09 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/21 19:29:35 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "shell.h"
#include "fill_line.h"
#include "libft.h"

int	load_history(t_shell *shell)
{
	char	*line;
	int		fd;
	t_list	*new;

	if ((fd = open(".shperso_history", O_RDONLY | O_CREAT, 0644)) == -1)
		return (0);
	while (get_next_line(fd, &line) == 1)
	{
		new = ft_lstnew(line, ft_strlen(line) + 1);
		ft_lstadd(&shell->history, new);
		free(line);
	}
	if (close(fd) == -1)
		return (0);
	return (1);
}

int	save_history(t_shell *shell)
{
	int		fd;
	t_list *curr;

	if ((fd = open(".shperso_history", O_WRONLY | O_APPEND | O_CREAT, 0644)) == -1)
		return (0);
	curr = shell->history;
	while (curr)
	{
		ft_dprintf(fd, "%s\n", curr->content);
		curr = curr->next;
	}
	if (close(fd) == -1)
		return (0);
	return (1);
}
