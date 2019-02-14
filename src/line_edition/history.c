/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 10:29:40 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/14 13:37:45 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>

#include "fill_line.h"
#include "libft.h"

void	clear_cmd_line(t_shell *shell)
{
	while (shell->line.cursor)
		ft_leftkey(shell);
	t_puts("cd");
}

int		ft_hisdown(t_shell *shell)
{
	t_list	*curr;
	int		i;

	if (!(curr = shell->history) || shell->line.mode != 0)
		return (0);
	i = 0;
	if (shell->his_pos > -1)
		shell->his_pos--;
	while (i < shell->his_pos && curr)
	{
		curr = curr->next;
		i++;
	}
	clear_cmd_line(shell);
	free_line(&shell->line);
	if (shell->his_pos > -1)
		ft_addchar(shell, curr->content);
	return (0);
}

int		ft_hisup(t_shell *shell)
{
	t_list	*curr;
	int		i;

	if (!(curr = shell->history) || shell->line.mode != 0)
		return (0);
	clear_cmd_line(shell);
	i = 0;
	if (shell->his_pos < (int)ft_lstlen(shell->history) - 1)
		shell->his_pos++;
	while (i < shell->his_pos && curr->next)
	{
		curr = curr->next;
		i++;
	}
	clear_cmd_line(shell);
	free_line(&shell->line);
	ft_addchar(shell, curr->content);
	return (0);
}
