/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_auto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:30:31 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/05 16:08:40 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <curses.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

static char	*g_builtins[] =\
{
	"unsetenv",
	"setenv",
	"exit"
};

void		ft_add_builtins(char *word, t_list **list)
{
	int		i;
	t_list	*new;

	i = 0;
	while (i < 3)
	{
		if (ft_strnequ(word, g_builtins[i], ft_strlen(word)))
		{
			new = ft_lstnew(g_builtins[i], ft_strlen(g_builtins[i]) + 1);
			ft_lstadd(list, new);
		}
		i++;
	}
}

char		*find_path(char *word)
{
	char	pwd[BUFF_SIZE];
	char	*ret;

	getcwd(pwd, BUFF_SIZE);
	ret = ft_strjoin(pwd, "/");
	if (!word)
		return (ret);
	if (*word != '/')
		ret = ft_strjoin_free(ret, word, 1);
	else
	{
		ft_strdel(&ret);
		if (!(ret = ft_strdup(word)))
			return (NULL);
	}
	if (ft_strchr(word, '/'))
		*(ft_strrchr(ret, '/') + 1) = 0;
	else
		*(ret + ft_strlen(pwd)) = 0;
	return (ret);
}

int			ft_comp(char *word, char *name)
{
	char	*rtn;

	if ((rtn = ft_strrchr(word, '/')))
	{
		if ((ft_strequ(".", name) || ft_strequ("..", name))
				&& *(rtn + 1) != '.')
			return (0);
		if (!*(rtn + 1) && !ft_strchr(word, '.'))
			return (1);
		return (ft_strnequ(rtn + 1, name, ft_strlen(rtn + 1)));
	}
	else
	{
		if ((ft_strequ(".", name) || ft_strequ("..", name))
				&& *word != '.')
			return (0);
		return (ft_strnequ(word, name, ft_strlen(word)));
	}
}

char		*word_to_complete(t_line *line)
{
	char	*ret;
	int		i;
	char	*buf;

	ret = NULL;
	i = 0;
	if (!(buf = ft_strdup(line->data)))
		return (NULL);
	buf[line->cursor] = 0;
	while (buf[i])
	{
		if (buf[i] == ' ' || buf[i] == ';' || buf[i] == '>' || buf[i] == '<'
			|| buf[i] == '&' || buf[i] == '|')
			ret = buf + i;
		i++;
	}
	if (ret)
		ret = ft_strdup(ret + 1);
	else
		ret = ft_strdup(buf);
	ft_strdel(&buf);
	return (ret);
}

int			is_a_command(t_line *line)
{
	int		ret;
	size_t	i;
	char	c;
	int		prev_word;

	i = 0;
	ret = 1;
	prev_word = -1;
	while (line->data[i] && i < line->cursor)
	{
		c = line->data[i];
		if ((c == ' ' || c == '>' || c == '<') && prev_word == 1)
			ret = 0;
		if (c == ';' || c == '&' || c == '|')
		{
			prev_word = -1;
			ret = 1;
		}
		if (c == '$')
			ret = 2;
		if (ft_isalnum(c) && prev_word < 1)
			prev_word = 1;
		i++;
	}
	return (ret);
}
