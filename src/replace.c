/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 12:16:25 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/08 12:52:10 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "libft.h"

static char	*add_var_values(t_shell *shell, char **dollars, char *arg)
{
	int		i;
	char	*var_value;

	i = 0;
	while (dollars[i])
	{
		if ((var_value = get_env_value(shell, dollars[i])))
		{
			if (!(arg = ft_strjoin_free(arg, var_value, 1)))
				return (NULL);
		}
		i++;
	}
	return (arg);
}

static char	*insert_var(t_shell *shell, char *arg)
{
	char	*ret;
	int		end_dollar;
	char	**dolz;
	int		len;

	end_dollar = (arg[ft_strlen(arg) - 1] == '$');
	len = ft_strlen(arg) - ft_strlen(ft_strchr(arg, '$'));
	if (!(ret = ft_strndup(arg, len)))
		return (NULL);
	if (!(dolz = ft_strsplit(ft_strchr(arg, '$'), "$")))
		return (NULL);
	if (!(ret = add_var_values(shell, dolz, ret)))
		return (NULL);
	if (end_dollar)
	{
		if (!(ret = ft_strjoin_free(ret, "$", 1)))
			return (NULL);
	}		
	ft_deltab(&dolz);
	return (ret);
}

static void	remove_backslash(char *arg, int *pos)
{
	ft_memmove(arg + *pos, arg + *pos + 1, ft_strlen(arg) - *pos - 1);
	arg[ft_strlen(arg) - *pos - 1] = 0;
	*pos += 2;
}

static char	*insert_home(t_shell *shell, char *arg)
{
	char	*home;
	char	*ret;

	if (!(home = get_env_value(shell, "HOME")))
		return (NULL);
	if (!(ret = ft_strjoin(home, arg + 1)))
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
		else if ((*arg)[pos] == CHAR_VAR && (*arg)[pos + 1])
		{
			if (!(*arg = insert_var(shell, *arg)))
				return (1);
		}
		else
			++pos;
	}
	return (0);
}
