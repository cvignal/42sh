/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 10:29:40 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/25 19:22:46 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_line.h"
#include "libft.h"

static void	clear_cmd_line(t_shell *shell)
{
	while (shell->line.cursor < shell->line.len)
		ft_rightkey(shell);
	ft_rightkey(shell);
	while (shell->line.cursor > 0)
		ft_backspace(shell);
}

void		ft_hisdown(t_shell *shell)
{
	t_list	*curr;
	int		i;

	if (!(curr = shell->history))
		return ;
	i = 0;
	if (shell->his_pos > -1)
		shell->his_pos--;
	while (i < shell->his_pos && curr)
	{
		curr = curr->next;
		i++;
	}
	clear_cmd_line(shell);
	if (shell->his_pos > -1)
	{
		ft_printf("%s", curr->content);
		shell->line.cursor = curr->content_size - 1;
		free_line(&shell->line);
		shell->line.data = ft_strdup(curr->content);
		shell->line.len = ft_strlen(shell->line.data);
		shell->line.alloc_size = curr->content_size;
	}
}

void		ft_hisup(t_shell *shell)
{
	t_list	*curr;
	int		i;

	clear_cmd_line(shell);
	if (!(curr = shell->history))
		return ;
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
	shell->line.data = ft_strdup(curr->content);
	shell->line.len = ft_strlen(shell->line.data);
	shell->line.alloc_size = curr->content_size;
	ft_printf("%s", shell->line.data);
	shell->line.cursor = curr->content_size - 1;
}
