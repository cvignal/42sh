/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:00:48 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:59:07 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static int	free_all(char *line)
{
	if (line)
		free(line);
	return (-1);
}

static int	ft_check(char *cpy, char **line, char **buf)
{
	char	*tmp;

	if (!(*buf = ft_strdup(ft_strchr(cpy, '\n') + 1)))
		return (free_all(*line));
	if (!(tmp = ft_strdup(*line)))
		return (free_all(*line));
	free(*line);
	if (!(*line = ft_strsub(tmp, 0, ft_strchr(tmp, '\n') - tmp)))
	{
		free(tmp);
		return (free_all(*line));
	}
	free(tmp);
	return (0);
}

static int	ft_read(int fd, char **line, char **buf, int *byt)
{
	char	*tmp;
	char	cpy[BUFF_SIZE + 1];

	while ((*byt = read(fd, cpy, BUFF_SIZE)))
	{
		if (*byt == -1)
			return (free_all(*line));
		cpy[*byt] = '\0';
		if (!(tmp = ft_strdup(*line)))
			return (free_all(*line));
		free(*line);
		if (!(*line = ft_strjoin(tmp, cpy)))
			return (free_all(*line));
		free(tmp);
		if (ft_strchr(cpy, '\n'))
		{
			if ((ft_check(cpy, line, buf)))
				return (free_all(*line));
			break ;
		}
	}
	return (*byt);
}

static int	ft_splitfun(char **line, char **buf)
{
	char		*tmp;

	free(*line);
	if (!(*line = ft_strsub(*buf, 0, ft_strchr(*buf, '\n') \
					- *buf)))
		return (free_all(*line));
	if (!(tmp = ft_strdup(ft_strchr(*buf, '\n') + 1)))
	{
		free(*buf);
		return (free_all(*line));
	}
	free(*buf);
	if (!(*buf = ft_strdup(tmp)))
	{
		free(tmp);
		return (free_all(*line));
	}
	free(tmp);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*buf[10240];
	int			byt;

	if (fd > 10239 || !line || fd < 0 || (!(*line = ft_strnew(0))))
		return (-1);
	byt = 0;
	if (buf[fd] && ft_strchr(buf[fd], '\n'))
		return (ft_splitfun(line, &buf[fd]));
	if (buf[fd])
	{
		free(*line);
		if (!(*line = ft_strdup(buf[fd])))
			return (-1);
		free(buf[fd]);
		buf[fd] = 0;
	}
	if (ft_read(fd, &(*line), &buf[fd], &byt) == -1)
		return (free_all(*line));
	if (byt < 1 && !ft_strlen(*line))
		return (byt + (free_all(*line) + 1));
	return (1);
}
