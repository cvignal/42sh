/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 14:15:01 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/10 17:13:07 by cvignal          ###   ########.fr       */
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
		display_list(shell, list);
		ft_strdel(&word);
		return ;
	}
	if (!list)
		return (ft_strdel(&word));
	str = list->content;
	if (ft_strchr(word, '/'))
		to_add = str + ft_strlen(ft_strrchr(word, '/') + 1);
	else
	{
		to_add = str + ft_strlen(word);
		if ((ft_strstr(word, "${")))
			to_add -= 2;
		else if (ft_strchr(word, '$'))
			to_add--;
	}
	ft_addchar(shell, to_add, 1);
	ft_strdel(&word);
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
		name = ft_escape(dirent->d_name);
		if (ft_comp(word, name))
		{
			if (dirent->d_type == 4)
				name = ft_strjoin_free(name, "/", 1);
			if (!name || !(new = ft_lstnew(name, ft_strlen(name) + 1)))
				return ;
			ft_lstadd(list, new);
		}
		ft_strdel(&name);
	}
	closedir(dir);
	ft_strdel(&path);
}

static void	ft_add_var(char *word, t_list **list, t_shell *shell)
{
	t_list	*new;
	t_var	*i;
	char	*name;
	char	*cpy;

	i = shell->vars;
	if (*word && (cpy = ft_strstr(word, "${")))
		cpy += 2;
	else
		cpy = ft_strchr(word, '$') + 1;
	while (i)
	{
		if (!(name = ft_strdup(i->var)))
			return ;
		name[ft_strlen(name) - ft_strlen(ft_strchr(name, '='))] = 0;
		if (ft_comp(cpy, name))
		{
			if (!(new = ft_lstnew(name, ft_strlen(name) + 1)))
				return ;
			ft_lstadd(list, new);
		}
		ft_strdel(&name);
		i = i->next;
	}
}

static void	ft_add_exec(char *word, t_list **list)
{
	char	**paths;
	int		i;
	char	*prog;

	if (ft_strchr(word, '/'))
		return (ft_add_files(word, list));
	if (!(paths = ft_strsplit(getenv("PATH"), ":")))
		return ;
	i = 0;
	while (paths[i])
	{
		if (!(prog = ft_strjoin(paths[i], "/")))
			return ;
		if (!(prog = ft_strjoin_free(prog, word, 1)))
			return ;
		ft_add_files(prog, list);
		ft_strdel(&prog);
		i++;
	}
	ft_add_builtins(word, list);
	if (!*list)
		ft_add_files(word, list);
	ft_deltab(&paths);
}

int			ft_tab(t_shell *shell)
{
	t_list	*list;
	char	*word;
	int		type;

	list = NULL;
	if (!shell->line.len)
		return (0);
	clean_under_line(NULL);
	if ((type = is_a_command(&shell->line)) == 1)
	{
		if (!(word = word_to_complete(&shell->line, 1)))
			return (0);
		ft_add_exec(word, &list);
	}
	else
	{
		word = word_to_complete(&shell->line, 0);
		!type ? ft_add_files(word, &list) : ft_add_var(word, &list, shell);
	}
	add_and_display(list, word, shell);
	ft_lstdel(&list, &ft_delelt);
	return (0);
}
