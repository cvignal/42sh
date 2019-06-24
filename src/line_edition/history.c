/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 10:29:40 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/11 11:03:11 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>

#include "fill_line.h"
#include "libft.h"

char	*g_save_line = NULL;

void	clear_cmd_line(t_shell *shell)
{
	int	nb;

	while (nb_multi_lines(shell, shell->line.cursor, shell->prompt_len) > 0)
		ft_lineup(shell);
	if (ft_strchr(shell->line.data, '\n'))
	{
		while (shell->line.cursor > 0)
			ft_leftkey(shell);
	}
	nb = shell->prompt_height;
	while (nb != 0)
	{
		t_puts("up");
		nb--;
	}
	t_puts("cr");
	t_puts("cd");
	if (!shell->ctrld)
		print_prompt(shell, shell->output ? 1 : 0);
	else
		print_prompt(shell, 1);
}

int		ft_hisdown(t_shell *shell)
{
	if (!shell->history || !shell->history->length)
		return (0);
	if (shell->his_pos < shell->history->length)
		shell->his_pos++;
	clear_cmd_line(shell);
	free_line(&shell->line);
	if (shell->his_pos < shell->history->length)
		ft_addchar(shell, shell->history->data[shell->his_pos], 1);
	else if (g_save_line)
	{
		ft_addchar(shell, g_save_line, 1);
		ft_strdel(&g_save_line);
	}
	return (0);
}

int		ft_hisup(t_shell *shell)
{
	if (!shell->history || !shell->history->length)
		return (0);
	if (shell->his_pos > 0)
		shell->his_pos--;
	clear_cmd_line(shell);
	if (shell->his_pos == shell->history->length - 1)
	{
		if (g_save_line)
			ft_strdel(&g_save_line);
		if (!(g_save_line = ft_strdup(shell->line.data)))
			return (1);
	}
	free_line(&shell->line);
	ft_addchar(shell, shell->history->data[shell->his_pos], 1);
	return (0);
}
