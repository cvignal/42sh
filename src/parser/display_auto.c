/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_auto.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 14:26:00 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/29 16:54:47 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <sys/ioctl.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

static void	fill_table(int *table, t_list *list)
{
	struct winsize	window;
	t_list			*curr;
	size_t			max_len;
	int				nb;

	ioctl(0, TIOCGWINSZ, &window);
	curr = list;
	max_len = 0;
	nb = 0;
	while (curr)
	{
		if (ft_strlen(curr->content) > max_len)
			max_len = ft_strlen(curr->content);
		curr = curr->next;
		nb++;
	}
	table[1] = (int)max_len;
	table[0] = window.ws_col / (max_len + 1);
	table[2] = nb;
	if (table[0] == 0)
		table[3] = nb;
	else
		table[3] = nb / table[0] + (nb % table[0] != 0);
}

static void	display_table(char **array, int table[4])
{
	int	i;
	int	j;

	ft_printf("\n");
	i = 0;
	if (table[0] == 0)
		table[1] = 0;
	while (i < table[3])
	{
		j = i;
		while (j < table[2])
		{
			ft_printf("%-*s", table[1] + 1, array[j]);
			j += table[3];
		}
		if (i + 1 < table[3])
			ft_printf("\n");
		i++;
	}
	ft_deltab(&array);
}

static int	ask_for_many_possibilities(int *table, t_curs *cursor)
{
	char	buf[10];
	int		ret;

	tputs(tgetstr("sc", NULL), 0, ft_printchar);
	if (table[2] < 75)
		return (1);
	else
	{
		ft_printf("\nsh: do you wish to see all %d possibilities (%d lines)? ",
				table[2], table[3]);
		ret = read(STDIN_FILENO, buf, 10);
		buf[ret] = 0;
		tputs(tgetstr("rc", NULL), 0, ft_printchar);
		if (cursor->line + 1 > tgetnum("li"))
			tputs(tgetstr("up", NULL), 0, ft_printchar);
		clean_under_line();
		return (buf[0] == 'y');
	}
}

void		display_list(t_list *list)
{
	int		table[4];
	char	**array;
	t_curs	*cursor;
	int		nb;

	tputs(tgetstr("sc", NULL), 0, ft_printchar);
	cursor = get_cursor_pos();
	fill_table(table, list);
	if (!ask_for_many_possibilities(table, cursor))
		return ;
	if (table[3] + cursor->line > tgetnum("li"))
		nb = table[3] + cursor->line - tgetnum("li") + 1;
	else
		nb = 0;
	array = ft_listtotab(list, table[2]);
	ft_bubblesort(array, table[2]);
	display_table(array, table);
	tputs(tgetstr("rc", NULL), 0, ft_printchar);
	while (--nb > 0)
		tputs(tgetstr("up", NULL), 0, ft_printchar);
	free(cursor);
}
