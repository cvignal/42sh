/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 14:15:01 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/29 15:22:24 by cvignal          ###   ########.fr       */
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
	ft_printf("%s", to_add);
	tputs(tgetstr("ei", NULL), 0, ft_printchar);
	add_to_line(&shell->line, to_add);
	ft_strdel(&word);
}

static int	first_arg(t_line *line)
{
	int		ret;
	size_t	i;

	ret = 1;
	i = 0;
	while (line->data[i] && i < line->cursor)
	{
		if ((line->data[i] == ' ' || line->data[i] == '>') && i > 0
				&& line->data[i - 1] != ';' && line->data[i - 1] != '|'
				&& !ft_strnequ(line->data + i - 1, "&&", 2))
			ret = 0;
		if (line->data[i] == ';' || line->data[i] == '|'
			|| ft_strnequ(line->data + i, "&&", 2)
			|| line->data[i] == '<')
			ret = 1;
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
		return ;
	while ((dirent = readdir(dir)) != NULL)
	{
		if (ft_comp(word, dirent->d_name))
		{
			if (dirent->d_type == 4)
				name = ft_strjoin(dirent->d_name, "/");
			else
				name = ft_strdup(dirent->d_name);
			new = ft_lstnew(name, ft_strlen(name) + 1);
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
	if (shell->line.mode != 0)
		return (0);
	clean_under_line();
	if (first_arg(&shell->line))
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
