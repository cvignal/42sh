/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:41:08 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/05 16:12:30 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "shell.h"
#include "fill_line.h"
#include "libft.h"

int		g_fd_output = -1;

static int	return_value_input(t_shell *shell, int res)
{
	if (!shell->line.alloc_size)
		shell->line.data = ft_strdup("");
	clean_under_line(shell);
	if (!shell->ctrld)
		if (expand_history(shell))
		{
			free_line(&shell->line);
			shell->line.data = ft_strnew(0);
		}
	if (!shell->end_heredoc)
		ft_dprintf(shell->fd_op, "\n");
	return (res == -1 || shell->line.data == NULL);
}

int			fill_line(t_shell *shell)
{
	char			buf[9];
	int				ret;
	int				res;

	res = 0;
	if (shell->history)
		shell->his_pos = shell->history->length;
	while (!res && (ret = read(0, buf, 8)) > 0)
	{
		buf[ret] = 0;
		if (is_a_special_key(buf))
		{
			if (apply_key(buf, shell))
				break ;
		}
		else
			res = ft_addchar(shell, buf, 0);
	}
	return (return_value_input(shell, res));
}
