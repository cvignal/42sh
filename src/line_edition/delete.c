/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 12:38:05 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/11 11:02:50 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "fill_line.h"

int	ft_delete(t_shell *shell)
{
	if (shell->line.cursor < shell->line.len)
	{
		shell->line.len--;
		if (nb_multi_lines(shell, shell->line.cursor + 1, shell->prompt_len)
				|| shell->line.data[shell->line.cursor] == '\n')
		{
			t_puts("sc");
			t_puts("cd");
			ft_dprintf(shell->fd_op, "%s", shell->line.data
					+ shell->line.cursor + 1);
			t_puts("rc");
		}
		else
			t_puts("dc");
		ft_del_char(shell->line.data, shell->line.cursor);
	}
	return (0);
}

int	ft_clearline(t_shell *shell)
{
	if (shell->line.cursor < shell->line.len)
	{
		while (shell->line.cursor != shell->line.len)
			ft_delete(shell);
	}
	return (0);
}
