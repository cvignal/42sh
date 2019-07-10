/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 12:18:42 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/10 17:19:53 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <curses.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

static char	*expand_tilde(char *word, char *ret)
{
	ft_strdel(&ret);
	if (!(ret = ft_strjoin("/Users/", getlogin())))
		return (NULL);
	if (!(ret = ft_strjoin_free(ret, word + 1, 1)))
		return (NULL);
	return (ret);
}

char		*find_path(char *word)
{
	char	pwd[MAX_PATH];
	char	*ret;

	getcwd(pwd, MAX_PATH);
	ret = ft_strjoin(pwd, "/");
	if (!word)
		return (ret);
	if (*word != '/' && (*word != '~' || !*(word + 1)))
		ret = ft_strjoin_free(ret, word, 1);
	else if (*word == '~' && *(word + 1))
	{
		if (!(ret = expand_tilde(word, ret)))
			return (NULL);
	}
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
