/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:11:35 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/20 17:09:53 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "fill_line.h"

static void	clean_curr_line(t_shell *shell)
{
	t_puts("cr");
	t_puts("cd");
	ft_dprintf(shell->fd_op, "(reverse-i-search)`%.*s': "
			, shell->line.len_search, shell->line.search);
}

int			hs_ctrlr(t_shell *shell)
{
	hs_search(shell, 1);
	return (0);
}

static int	hs_display_res(t_shell *shell, t_list *elt, int i, size_t len)
{
	int		nb;

	clean_curr_line(shell);
	ft_dprintf(shell->fd_op, "%s", elt->content);
	nb = len + 1;
	shell->line.curs_search = elt->content_size - 1 - len;
	while (--nb)
		t_puts("le");
	shell->line.len_search++;
	shell->his_pos = i;
	return (0);
}

int			hs_search(t_shell *shell, int flag)
{
	int		i;
	t_list	*curr;
	char	*res;

	curr = shell->history;
	i = -1;
	while (++i < shell->his_pos && curr)
		curr = curr->next;
	if (flag && curr)
	{
		curr = curr->next;
		i++;
	}
	shell->line.curs_search = 0;
	while (curr)
	{
		if ((res = ft_strrstr(curr->content, shell->line.search)))
			return (hs_display_res(shell, curr, i, ft_strlen(res)));
		curr = curr->next;
		i++;
	}
	return (1);
}
