/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:02:21 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/06 15:43:34 by cvignal          ###   ########.fr       */
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
		ft_bzero(line->data + i + add_len + line->len - i - old_len
				, old_len - add_len);
	ft_strncpy(line->data + i, value, add_len);
	line->len += add_len;
	return (0);
}

static int	buffer_size(char *str, int i)
{
	int	j;
	int	ret;
	int	nb;

	j = i + 1;
	nb = 0;
	ret = 0;
	if (str[j] && (ft_isdigit(str[j]) || str[j] == '-'))
	{
		j++;
		nb = 1;
		ret++;
	}
	while (str[j] && str[j] != ' ' && !ft_strchr(META_CHARS, str[j]))
	{
		if (nb && !ft_isdigit(str[j]))
			break ;
		ret++;
		if ((str[j] == '!' && j == i + 1))
			break ;
		j++;
	}
	return (ret);
}

int			replace_exclamation_mark(t_shell *shell, int i, int flag)
{
	int		buf_size;
	char	*buf;

	if (flag && shell->line.data[i + 1] == '=')
		return (i);
	buf_size = buffer_size(shell->line.data, i);
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
	return (i + buf_size - 1);
}

int			exp_replace_history(t_shell *shell, char *buf, int i)
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
