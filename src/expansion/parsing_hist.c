/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:02:21 by cvignal           #+#    #+#             */
/*   Updated: 2019/05/15 14:14:11 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "fill_line.h"
#include "expand.h"

int		replace_exclamation_mark(t_shell *shell, int i)
{
	int		j;
	int		buf_size;
	char	*buf;

	j = i + 1;
	buf_size = 0;
	while (shell->line.data[j] && shell->line.data[j] != ' '
			&& !ft_strchr(META_CHARS, shell->line.data[j]))
	{
		j++;
		buf_size++;
	}
	if (!buf_size)
		return (i);
	if (!(buf = ft_strsub(shell->line.data, i, buf_size + 1)))
		return (-1);
	if (exp_replace_history(shell, buf))
		return (-1);
	ft_strdel(&buf);
	return (i + buf_size);
}

int		exp_replace_history(t_shell *shell, char *buf)
{
	char	*value;

	if (!(value = exp_find_cmd(shell->history, buf + 1)))
		return (1);
	if (!(shell->line.data = ft_replace_all(shell->line.data, buf, value, 1)))
		return (1);
	return (0);
}
