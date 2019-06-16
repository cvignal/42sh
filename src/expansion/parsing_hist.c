/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:02:21 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/16 18:11:16 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "fill_line.h"
#include "expand.h"

static int	realloc_line(t_line *line)
{
	char			*new_data;
	unsigned int	i;

	if (!(new_data = ft_strnew(line->alloc_size + LINE_ALLOC_SIZE)))
		return (1);
	i = 0;
	while (i < line->len)
	{
		new_data[i] = line->data[i];
		++i;
	}
	ft_bzero(new_data + i, line->alloc_size + LINE_ALLOC_SIZE - i + 1);
	if (line->data)
		free(line->data);
	line->data = new_data;
	line->alloc_size += LINE_ALLOC_SIZE;
	return (0);
}

static int	replace_in_line(t_line *line, char *buf, char *value, int i)
{
	size_t	add_len;
	size_t	old_len;

	add_len = ft_strlen(value);
	old_len = ft_strlen(buf);
	while (line->len + add_len - old_len + 1 >= line->alloc_size)
	{
		if (realloc_line(line))
			return (1);
	}
	ft_memmove(line->data + i + add_len, line->data + i + old_len,
			line->len - i - old_len);
	if (old_len > add_len)
		ft_bzero(line->data + i + add_len + line->len - i - old_len, old_len - add_len); 
	ft_strncpy(line->data + i, value, add_len);
	line->len += add_len;
	return (0);
}

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
		buf_size++;
		if (shell->line.data[j] == '!' && j == i + 1)
			break ;
		j++;
	}
	if (!buf_size)
		return (i);
	if (!(buf = ft_strsub(shell->line.data, i, buf_size + 1)))
		return (-1);
	if ((buf_size = exp_replace_history(shell, buf, i)) == -1)
	{
		ft_strdel(&buf);
		return (-1);
	}
	ft_strdel(&buf);
	return (i + buf_size);
}

int		exp_replace_history(t_shell *shell, char *buf, int i)
{
	char	*value;

	if (!(value = exp_find_cmd(shell->history, buf + 1)))
	{
		shell->fc_cmd = 1;
		return (-1);
	}
	if (replace_in_line(&shell->line, buf, value, i))
		return (-1);
	return (ft_strlen(value));
}
