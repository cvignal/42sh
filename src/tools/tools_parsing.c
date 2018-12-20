/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 15:50:52 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/11 15:48:27 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

char	*ft_tilt(char *arg, char **env)
{
	char	*home;

	if (!arg[1] || (arg[1] != '-' && arg[1] != '+'))
	{
		if (!(home = ft_getenv(env, "HOME")))
			return (NULL);
		home = ft_strjoin_free(home, arg + 1, 0);
	}
	else if (arg[1] == '-')
	{
		if (!(home = ft_getenv(env, "OLDPWD")))
			return (NULL);
		home = ft_strjoin_free(home, arg + 2, 0);
	}
	else
	{
		if (!(home = ft_getenv(env, "PWD")))
			return (NULL);
		home = ft_strjoin_free(home, arg + 2, 0);
	}
	ft_strdel(&arg);
	return (home);
}

char	*ft_dollar(char *arg, char **env)
{
	char	*ret;
	int		len;
	char	**dolz;
	int		i;

	len = ft_strlen(arg) - ft_strlen(ft_strchr(arg, '$'));
	if (!(ret = ft_strndup(arg, len)))
		return (NULL);
	dolz = ft_strsplit(ft_strchr(arg, '$'), "$");
	i = 0;
	while (dolz[i])
	{
		if (ft_getenv(env, dolz[i]))
			ret = ft_strjoin_free(ret, ft_getenv(env, dolz[i]), 1);
		i++;
	}
	ft_deltab(&dolz);
	return (ret);
}

char	**ft_replace(char **args, char **env)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '~')
			args[i] = ft_tilt(args[i], env);
		else if (ft_strchr(args[i], '$'))
			args[i] = ft_dollar(args[i], env);
		i++;
	}
	return (args);
}
