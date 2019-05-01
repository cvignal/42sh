/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:35:26 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/01 22:29:30 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>

#include "shell.h"
#include "expand.h"
#include "libft.h"

static char			*get_target_str(const char *arg)
{
	char	*cut;
	int		i;

	cut = NULL;
	if (arg[0] == '~')
	{
		i = 1;
		while (arg[i] && arg[i] != '/')
			++i;
		if (!(cut = ft_strndup(arg + 1, i - 1)))
			return (NULL);
	}
	return (cut);
}

static char			*replace_home(char *src, const char *home_value,
		size_t len_target)
{
	size_t	len_src;
	size_t	len_home;
	char	*ret;

	len_src = ft_strlen(src);
	len_home = ft_strlen(home_value);
	if ((ret = malloc(sizeof(*ret) * (len_src + len_home + 1))))
	{
		ft_strcpy(ret, home_value);
		ft_strcpy(ret + len_home, src + len_target + 1);
	}
	return (ret);
}

static const char	*get_home_value(t_shell *shell, const char *target,
		size_t len_target)
{
	struct passwd	*passwd;

	if ((len_target = ft_strlen(target)) == 0)
		return (get_var_value(get_var(shell->vars, "HOME")));
	else if ((passwd = getpwnam(target)))
		return (passwd->pw_dir);
	return (NULL);
}

int					expand_home(t_shell *shell, const char *arg)
{
	char			*target;
	const char		*value;
	char			*expanded;
	size_t			len_target;

	if (!(target = get_target_str(arg)))
		return (0);
	len_target = ft_strlen(target);
	value = get_home_value(shell, target, len_target);
	free(target);
	if (value)
	{
		if ((expanded = replace_home(shell->exp_lexer.ret.data[0],
					value, len_target)))
		{
			free(shell->exp_lexer.ret.data[0]);
			shell->exp_lexer.ret.data[0] = expanded;
		}
		else
			return (1);
	}
	return (0);
}
