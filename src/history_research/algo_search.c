/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:11:35 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/20 14:46:38 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "fill_line.h"

static void	clean_curr_line(t_shell *shell)
{
	t_puts("cr");
	t_puts("cd");
	ft_dprintf(shell->fd_op, "(reverse-i-search)`%.*s': ", shell->line.len_search, shell->line.search);
}

int	hs_ctrlr(t_shell *shell)
{
	hs_search(shell, 1);
	return (0);
}

int	hs_search(t_shell *shell, int flag)
{
	int		i;
	t_list	*curr;
	char	*res;
	int		nb;

	curr = shell->history;
	i = -1;
	while (++i < shell->his_pos && curr)
		curr = curr->next;
	if (flag && curr)
	{
		curr = curr->next;
		i++;
	}
	while (curr)
	{
		if ((res = ft_strstr(curr->content, shell->line.search)))
		{
			clean_curr_line(shell);
			ft_dprintf(shell->fd_op, "%s", curr->content);
			nb = curr->content_size;
			while (--nb)
				t_puts("le");
			shell->line.len_search++;
			shell->his_pos = i;
			return (0);
		}
		curr = curr->next;
		i++;
	}
	return (1);
}
