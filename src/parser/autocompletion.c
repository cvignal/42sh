/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:09:30 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/23 17:30:41 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "fill_line.h"
#include <dirent.h>
#include <stdlib.h>

void		add_and_display(char *str, char *word, t_cmdline *res)
{
	char	*to_add;

	if (ft_strchr(word, '/'))
		to_add = str + ft_strlen(ft_strrchr(word, '/') + 1);
	else
		to_add = str + ft_strlen(word);
	ft_printf("%s", to_add);
	res->str = ft_insert_free(res->str, to_add, res->cursor, 1);
	res->cursor = ft_strlen(res->str);
}

static int	first_arg(char *line)
{
	
	return (1);
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
		}
	}
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
	ft_deltab(&paths);
}

void		ft_tab(t_cmdline *res, t_shell *shell)
{
	t_list	*list;
	char	*word;

	(void)shell;
	list = NULL;
	clean_under_line();
	if (first_arg(res->str))
	{
		word = res->str;
		if (!*word)
			return ;
		ft_add_exec(word, &list);
	}
	else
	{
		word = ft_strrchr(res->str, ' ') + 1;
		ft_add_files(word, &list);
	}
	if (list && list->next)
		display_list(list);
	else if (list)
		add_and_display(list->content, word, res);
	ft_lstdel(&list, &ft_delelt);
}
