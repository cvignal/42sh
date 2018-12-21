/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:01:47 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/21 14:30:03 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"

static int	realloc_heredoc(t_heredoc *heredoc, size_t len)
{
	char			*new_str;
	size_t			alloc_size;
	unsigned int	i;

	alloc_size = (len / HEREDOC_ALLOC_SIZE + 1) * HEREDOC_ALLOC_SIZE;
	new_str = malloc(sizeof(*new_str) * alloc_size);
	if (!new_str)
		return (1);
	i = 0;
	while (i < heredoc->len)
	{
		new_str[i] = heredoc->data[i];
		++i;
	}
	new_str[i] = 0;
	free(heredoc->data);
	heredoc->data = new_str;
	heredoc->alloc_size = alloc_size;
	return (0);
}

t_heredoc	*alloc_heredoc(void)
{
	t_heredoc	*heredoc;

	heredoc = malloc(sizeof(*heredoc));
	if (!heredoc)
		return (NULL);
	ft_bzero(heredoc, sizeof(*heredoc));
	return (heredoc);
}

int			add_to_heredoc(t_heredoc *heredoc, const char *line)
{
	size_t			len;
	unsigned int	i;

	len = ft_strlen(line) + 2;
	if (len >= heredoc->alloc_size)
	{
		if (realloc_heredoc(heredoc, len))
			return (1);
	}
	i = 0;
	while (i < len)
		heredoc->data[heredoc->len++] = line[i++];
	heredoc->data[heredoc->len++] = '\n';
	heredoc->data[heredoc->len] = 0;
	return (0);
}

int			read_heredoc(t_heredoc *heredoc, t_redir *redir)
{
	char		*line;
	int			ret;

	while ((ret = get_next_line(0, &line)))
	{
		if (!ft_strcmp(redir->target, line))
		{
			free(line);
			break ;
		}
		else if (add_to_heredoc(heredoc, line))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

int			heredoc_exit_error(t_heredoc *heredoc)
{
	if (heredoc->data)
		free(heredoc->data);
	free(heredoc);
	return (1);
}
