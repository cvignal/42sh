/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 14:15:01 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/11 14:19:56 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

static void	add_and_display(t_list *list, char *word, t_shell *shell)
{
	char	*to_add;
	char	*str;

	if (list && list->next)
	{
		display_list(list);
		ft_strdel(&word);
		return ;
	}
	if (!list)
	{
		ft_strdel(&word);
		return ;
	}
	str = list->content;
	if (ft_strchr(word, '/'))
		to_add = str + ft_strlen(ft_strrchr(word, '/') + 1);
	else
		to_add = str + ft_strlen(word);
	tputs(tgetstr("im", NULL), 0, ft_printchar);
	ft_dprintf(g_fd_output, "%s", to_add);
	tputs(tgetstr("ei", NULL), 0, ft_printchar);
	add_to_line(&shell->line, to_add);
	ft_strdel(&word);
}

static int	is_a_command(t_line *line)
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
		if (ft_isalnum(c) && prev_word < 1)
			prev_word = 1;
		i++;
	}
	return (ret);
}

static void	ft_add_files(char *word, t_list **list)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*path;
	t_list			*new;
	char			*name;

	path = find_path(word);
	if (!(dir = opendir(path)))
		return (ft_strdel(&path));
	while ((dirent = readdir(dir)) != NULL)
	{
		if (ft_comp(word, dirent->d_name))
		{
			name = dirent->d_type != 4 ? ft_strdup(dirent->d_name)
				: ft_strjoin(dirent->d_name, "/");
			if (!name || !(new = ft_lstnew(name, ft_strlen(name) + 1)))
				return ;
			ft_lstadd(list, new);
			ft_strdel(&name);
		}
	}
	closedir(dir);
	ft_strdel(&path);
}

static void	ft_add_exec(char *word, t_list **list)
{
	char	**paths;
	int		i;
	char	*prog;

	if (ft_strchr(word, '/'))
	{
		ft_add_files(word, list);
		return ;
	}
	paths = ft_strsplit(getenv("PATH"), ":");
	i = 0;
	while (paths[i])
	{
		prog = ft_strjoin(paths[i], "/");
		prog = ft_strjoin_free(prog, word, 1);
		ft_add_files(prog, list);
		ft_strdel(&prog);
		i++;
	}
	ft_add_builtins(word, list);
	ft_deltab(&paths);
}

int			ft_tab(t_shell *shell)
{
	t_list	*list;
	char	*word;

	list = NULL;
	if (shell->line.mode != 0 || !shell->line.len)
		return (0);
	clean_under_line(NULL);
	if (is_a_command(&shell->line))
	{
		if (!word_to_complete(&shell->line))
			word = ft_strdup(shell->line.data);
		else
			word = word_to_complete(&shell->line);
		if (!*word)
			return (0);
		ft_add_exec(word, &list);
	}
	else
	{
		word = word_to_complete(&shell->line);
		ft_add_files(word, &list);
	}
	add_and_display(list, word, shell);
	ft_lstdel(&list, &ft_delelt);
	return (0);
}
