/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:09:30 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/20 14:28:11 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>

void	add_and_display(char *str, char *word, t_cmdline *res)
{
	char	*to_add;

	ft_printf("|str : %s|", str);
	if (file_type(str) == 'd')
		str = ft_strjoin_free(str, "/", 1);
	if (ft_strchr(word, '/'))
		to_add = str + ft_strlen(ft_strrchr(word, '/') + 1);
	else
		to_add = str + ft_strlen(word);
	ft_printf("%s", to_add);
	res->str = ft_strjoin_free(res->str, to_add, 1);
	res->cursor = ft_strlen(res->str);
}

static int	first_arg(char *line)
{
	if (ft_strchr(line, ' '))
		return (0);
	return (1);
}

static void	ft_add_files(char *word, t_list **list)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*path;
	t_list			*new;

	path = find_path(word);
	dir = opendir(path);
	while ((dirent = readdir(dir)) != NULL)
	{
		if (ft_comp(word, dirent->d_name))
		{
			new = ft_lstnew(ft_strdup(dirent->d_name), ft_strlen(dirent->d_name));
			ft_lstadd(list, new);
		}
	}
}

static void	ft_add_exec(char *word, t_list **list)
{
	char	**paths;
	int		i;
	char	*prog;

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

void	ft_tab(t_cmdline *res)
{
	t_list	*list;
	char	*word;

	list = NULL;
	if (first_arg(res->str))
	{
		word = res->str;
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
//	ft_lstdel(&list, &ft_delelt);
}
