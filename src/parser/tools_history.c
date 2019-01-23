/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:47:09 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/23 12:01:27 by gchainet         ###   ########.fr       */
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
	t_list	*new;

	if ((shell->fd = open(".shperso_history",
					O_RDWR | O_APPEND | O_CREAT, 0644)) == -1)
		return (0);
	while (get_next_line(shell->fd, &line) == 1)
	{
		new = ft_lstnew(line, ft_strlen(line) + 1);
		ft_lstadd(&shell->history, new);
		free(line);
	}
	return (1);
}
