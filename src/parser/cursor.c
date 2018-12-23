/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 14:11:53 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/23 16:41:05 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>
#include <unistd.h>
#include "libft.h"
#include "fill_line.h"

void	read_cursor_pos(char *buf)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (c != 'R')
	{
		c = 0;
		read(0, &c, 1);
		buf[i] = c;
		i++;
	}
	buf[i] = 0;
}

t_curs	*get_cursor_pos(void)
{
	char	buf[30];
	t_curs	*res;

	if (!(res = (t_curs*)malloc(sizeof(t_curs))))
		return (NULL);
	write(1, CURS_POS, 4);
	read_cursor_pos(buf);
	res->line = ft_atoi(buf + 2);
	res->col = ft_atoi(ft_strchr(buf, ';') + 1);
	return (res);
}
