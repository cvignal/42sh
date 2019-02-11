/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:01:47 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/08 14:08:08 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

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
	while (i < len - 2)
		heredoc->data[heredoc->len++] = line[i++];
	heredoc->data[heredoc->len++] = '\n';
	heredoc->data[heredoc->len] = 0;
	return (0);
}

int			read_heredoc(t_heredoc *heredoc, t_redir *redir)
{
	t_shell	tmp_shell;

	ft_bzero(&tmp_shell, sizeof(tmp_shell));
	tmp_shell.ctrld = 1;
	tmp_shell.end_heredoc = 0;
	while (!fill_line(&tmp_shell))
	{
		if (tmp_shell.end_heredoc
				|| !ft_strcmp(redir->target, tmp_shell.line.data))
		{
			free_line(&tmp_shell.line);
			if (tmp_shell.end_heredoc == 2)
				ft_strdel(&heredoc->data);
			break ;
		}
		else if (add_to_heredoc(heredoc, tmp_shell.line.data))
		{
			free_line(&tmp_shell.line);
			return (1);
		}
		free_line(&tmp_shell.line);
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
