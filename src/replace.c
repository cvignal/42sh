/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 12:16:25 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/08 10:29:25 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "libft.h"

static char	*insert_var(t_shell *shell, char *arg, int pos)
{
	int		len_name;
	int		len_rest;
	char	*var_value;
	char	*var_name;
	char	*ret;

	len_name = ft_strlen(arg + pos) - ft_strlen(ft_strchr(arg + pos + 1, '$'));
	len_rest = ft_strlen(arg) - pos - len_name;
	if (!(var_name = ft_strndup(arg + pos, len_name)))
		return (NULL);
	var_value = get_env_value(shell, var_name);
	if (!(ret = ft_insert_free(arg, var_value, pos, 0)))
		return (NULL);
	return (ret);
}

static void	remove_backslash(char *arg, int *pos)
{
	ft_memmove(arg + *pos, arg + *pos + 1, ft_strlen(arg) - *pos - 1);
	*pos += 2;
}

static char	*insert_home(t_shell *shell, char *arg)
{
	char	*home;
	char	*ret;

	if (!(home = get_env_value(shell, "HOME")))
		return (NULL);
	if (!(ret = ft_strjoin(arg + 1, home)))
		return (NULL);
	return (ret);
}

int			expand_vars(t_shell *shell, char **arg)
{
	int	pos;

	pos = 0;
	if ((*arg)[0] == '~')
	{
		if (!((*arg) = insert_home(shell, *arg)))
			return (1);
	}
	while ((*arg)[pos])
	{
		if ((*arg)[pos] == '\\' && (*arg)[pos + 1] && ((*arg)[pos + 1] == CHAR_VAR
					|| (*arg)[pos + 1] == '~'))
			remove_backslash(*arg, &pos);
		else if ((*arg)[pos] == CHAR_VAR && pos > 0)
		{
			if (!(*arg = insert_var(shell, *arg, pos)))
				return (1);
		}
		else
			++pos;
	}
	return (0);
}
