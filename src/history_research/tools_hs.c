/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_hs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:11:46 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/20 16:56:34 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_line.h"
#include "libft.h"
#include "shell.h"

void	display_char_in_research(t_shell *shell, char c)
{
	size_t	nb;

	nb = 4 + shell->line.curs_search;
	while (--nb)
		t_puts("le");
	t_puts("im");
	ft_dprintf(shell->fd_op, "%c", c);
	t_puts("ei");
	while (++nb != 4 + shell->line.curs_search)
		t_puts("nd");
}

void	fill_line_hs(t_shell *shell, char *buf)
{
	int		i;
	t_list	*curr;

	t_puts("cr");
	t_puts("dl");
	print_prompt(NULL, shell, 0);
	i = -1;
	curr = shell->history;
	while (++i < shell->his_pos)
		curr = curr->next;
	ft_addchar(shell, curr->content, 0);
	if (is_a_special_key(buf))
		apply_key(buf, shell);
}
