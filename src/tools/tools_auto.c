/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_auto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:30:31 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/20 13:36:56 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <term.h>
#include <curses.h>

static void	fill_table(int *table, t_list *list)
{
	int		width;
	t_list	*curr;
	size_t	max_len;
	int		nb;

	width = tgetnum("co");
	curr = list;
	max_len = 0;
	nb = 0;
	while (curr)
	{
		if (ft_strlen(curr->content) > max_len)
			max_len = ft_strlen(curr->content);
		curr = curr->next;
		nb++;
	}
	table[1] = (int)max_len;
	table[0] = width / (max_len + 1);
	table[2] = nb;
}

char	*find_path(char *word)
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
		ret = ft_strdup(word);
	if (ft_strchr(word, '/'))
		*(ft_strrchr(ret, '/') + 1) = 0;
	else
		*(ret + ft_strlen(pwd)) = 0;
	return (ret);
}

int		ft_comp(char *word, char *name)
{
	char	*rtn;

	if ((rtn = ft_strrchr(word, '/')))
	{
		if (!*(rtn + 1) && !ft_strchr(word, '.'))
			return (1);
		return (ft_strnequ(rtn + 1, name, ft_strlen(rtn + 1)));
	}
	else
		return (ft_strnequ(word, name, ft_strlen(word)));
}

void	display_list(t_list *list)
{
	t_list	*curr;
	int		i;
	int		table[3];
	
	curr = list;
	tputs(tgetstr("sc", NULL), 0, ft_printchar);
	fill_table(table, list);
	ft_printf("\n");
	ft_printf("max len : %d nb elem : %d\n", table[1], table[2]);
	i = 0;
	while (curr)
	{
		while (i < tab[0] && curr)
		{
			ft_printf("%*s ", tab[1] + 1, curr->content);
			curr = curr->next;
			i++;
		}
		i = 0;
		ft_printf("\n");
	}
	tputs(tgetstr("rc", NULL), 0, ft_printchar);
}
