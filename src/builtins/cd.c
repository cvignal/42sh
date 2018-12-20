/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 10:23:37 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/17 21:35:05 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

int		ft_special_cases(char **args, char ***env)
{
	char	*path;

	if (!*args)
	{
		if (!(path = ft_getenv(*env, "HOME")))
		{
			ft_printf("cd: HOME not set\n");
			return (0);
		}
	}
	else
	{
		if (!(path = ft_getenv(*env, "OLDPWD")))
		{
			ft_printf("cd: OLDPWD not set\n");
			return (0);
		}
	}
	return (ft_cd(&path, env));
}

int		follow_symlinks(char **args, char ***env)
{
	char	*link;
	int		len;

	if (file_type(*(args + 1)) != 'l')
		return (ft_cd(args + 1, env));
	if (!(link = ft_strnew(1023)))
		return (0);
	if ((len = readlink(*(args + 1), link, 1023)) != -1)
	{
		link[len] = 0;
		if (link[0] != '/' && ft_strchr(args[1], '/'))
			link = ft_join_path(args[1], link);
		ft_cd(&link, env);
		ft_strdel(&link);
	}
	return (1);
}

char	**ft_update_env(char *path, char **env, int old)
{
	char	*new_pwd;

	if (!(new_pwd = old ? ft_strdup("OLDPWD=") : ft_strdup("PWD=")))
		return (0);
	if (!(new_pwd = ft_strjoin_free(new_pwd, path, 1)))
		return (0);
	env = ft_setenv(&new_pwd, env);
	ft_strdel(&new_pwd);
	return (env);
}

int		ft_cd(char **args, char ***env)
{
	char	pwd[BUFF_SIZE];

	if (!*args || ft_strequ(args[0], "-"))
		return (ft_special_cases(args, env));
	if (ft_strequ(args[0], "-P"))
		return (follow_symlinks(args, env));
	if (access(args[0], F_OK))
	{
		ft_printf("cd: no such file or directory: %s\n", args[0]);
		return (0);
	}
	else if (access(args[0], R_OK))
	{
		ft_printf("cd: permission denied: %s\n", args[0]);
		return (0);
	}
	getcwd(pwd, BUFF_SIZE);
	if (!(*env = ft_update_env(pwd, *env, 1)))
		return (0);
	chdir(args[0]);
	getcwd(pwd, BUFF_SIZE);
	if (!(*env = ft_update_env(pwd, *env, 0)))
		return (0);
	return (1);
}
