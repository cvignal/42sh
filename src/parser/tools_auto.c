/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_auto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:30:31 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/30 16:38:37 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <curses.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

char	*g_builtins[] =\
{
	"unsetenv",
	"setenv",
	"exit",
	"echo",
	"env"
};

void		ft_add_builtins(char *word, t_list **list)
{
	int		i;
	t_list	*new;

	i = 0;
	while (i < 5)
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
		ret = ft_strdup(word);
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
	ft_strdel(&buf);
	return (ret);
}

void		clean_under_line(t_shell *shell)
{
	tputs(tgetstr("sc", NULL), 0, ft_printchar);
	if (shell)
	{
		while (shell->line.cursor < shell->line.len)
			ft_rightkey(shell);
	}
	tputs(tgetstr("cd", NULL), 0, ft_printchar);
	if (!shell)
		tputs(tgetstr("rc", NULL), 0, ft_printchar);
}
