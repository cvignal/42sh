/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_auto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:30:31 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/27 16:11:22 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <curses.h>

#include "21sh.h"
#include "libft.h"
#include "fill_line.h"

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
		ret = ft_strdup(word);
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

char		*word_to_complete(char *line)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == ';' || line[i] == '>' || line[i] == '<'
			|| line[i] == '&' || line[i] == '|')
			ret = line + i;
		i++;
	}
	return (ret);
}

void		clean_under_line(void)
{
	tputs(tgetstr("sc", NULL), 0, ft_printchar);
	ft_printf("\n");
	tputs(tgetstr("cd", NULL), 0, ft_printchar);
	tputs(tgetstr("rc", NULL), 0, ft_printchar);
}
