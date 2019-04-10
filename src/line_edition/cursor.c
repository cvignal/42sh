/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 14:11:53 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/01 11:33:50 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "fill_line.h"

void	read_cursor_pos(char *buf)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (c != 'R' && i < 28)
	{
		c = 0;
		read(0, &c, 1);
		buf[i] = c;
		i++;
	}
	buf[i] = 0;
}

void	get_cursor_pos(t_curs *cursor)
{
	char	buf[25];

	write(g_fd_output, CURS_POS, 4);
	read_cursor_pos(buf);
	cursor->line = ft_atoi(buf + 2);
	if (ft_strchr(buf, ';'))
		cursor->col = ft_atoi(ft_strchr(buf, ';') + 1);
	else
		cursor->col = 1;
}
