/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_hs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:11:46 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/23 12:44:56 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_line.h"
#include "libft.h"
#include "shell.h"

void	display_char_in_research(t_shell *shell, char c)
{
	size_t	nb;

	t_puts("rc");
	nb = 4;
	while (--nb)
		t_puts("le");
	t_puts("im");
	ft_dprintf(shell->fd_op, "%c", c);
	t_puts("ei");
	while (++nb != 4)
		t_puts("nd");
	t_puts("sc");
}

void	fill_line_hs(t_shell *shell, char *buf)
{
	t_puts("rc");
	t_puts("cr");
	t_puts("cd");
	print_prompt(shell, 0);
	if (shell->his_pos == shell->history->length)
		return ;
	if (shell->his_pos < 0)
		shell->his_pos = 0;
	ft_addchar(shell, shell->history->data[shell->his_pos], 1);
	while (shell->line.cursor > shell->line.curs_search)
		ft_leftkey(shell);
	if (is_a_special_key(buf))
		apply_key(buf, shell);
}
