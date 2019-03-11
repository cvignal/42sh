/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:11:35 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/11 15:42:58 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "fill_line.h"

static void	clean_curr_line(t_shell *shell)
{
	t_puts("rc");
	t_puts("cr");
	t_puts("cd");
	ft_dprintf(shell->fd_op, "(reverse-i-search)`%.*s': "
			, shell->line.len_search + 1, shell->line.search);
	t_puts("sc");
}

int			hs_ctrlr(t_shell *shell)
{
	hs_search(shell, 1);
	return (0);
}

static int	hs_display_res(t_shell *shell, int i, size_t len)
{
	int		nb;

	clean_curr_line(shell);
	ft_dprintf(shell->fd_op, "%s", shell->history->data[i]);
	nb = len + 1;
	shell->line.curs_search = ft_strlen(shell->history->data[i]) - 1 - len;
	while (--nb)
		t_puts("le");
	shell->line.len_search++;
	shell->his_pos = i;
	return (0);
}

int			hs_search(t_shell *shell, int flag)
{
	int		i;
	char	*res;

	i = shell->his_pos - flag;
	if (i == shell->history->length)
		i--;
	shell->line.curs_search = 0;
	while (i > 0)
	{
		if ((res = ft_strrstr(shell->history->data[i], shell->line.search)))
			return (hs_display_res(shell, i, ft_strlen(res)));
		i--;
	}
	return (1);
}
