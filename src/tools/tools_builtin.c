/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 13:08:19 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/17 17:10:14 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/stat.h>

int		builtin(char *arg)
{
	return (ft_strequ(arg, "cd") || ft_strequ(arg, "echo")
			|| ft_strequ(arg, "env") || ft_strequ(arg, "exit")
			|| ft_strequ(arg, "setenv") || ft_strequ(arg, "unsetenv"));
}

int		exec_builtin(char **args, char ***env, char *line)
{
	if (ft_strequ(args[0], "echo"))
		ft_echo(args + 1);
	else if (ft_strequ(args[0], "cd"))
		ft_cd(args + 1, env);
	else if (ft_strequ(args[0], "env"))
		ft_env(args + 1, (const char **)(*env), line);
	else if (ft_strequ(args[0], "exit"))
		ft_exit(args + 1, *env, line);
	else if (ft_strequ(args[0], "setenv"))
	{
		while (*args)
			*env = ft_setenv(++args, *env);
	}
	else if (ft_strequ(args[0], "unsetenv"))
		*env = ft_unsetenv(args + 1, *env);
	return (1);
}

char	*ft_join_path(char *path, char *link)
{
	char	*ret;
	int		len;

	len = ft_strlen(path);
	if (!(ret = ft_strnew(len + ft_strlen(link) + 1)))
		return (NULL);
	len = len - ft_strlen(ft_strrchr(path, '/')) + 1;
	ft_strncpy(ret, path, len);
	ft_strcat(ret, link);
	ft_strdel(&link);
	return (ret);
}

char	file_type(char *path)
{
	struct stat info;

	if (lstat(path, &info) != -1)
	{
		if (S_ISLNK(info.st_mode))
			return ('l');
		else
			return ('c');
	}
	return ('f');
}

void	ft_exit(char **args, char **env, char *line)
{
	char	i;

	if (!args || !args[0])
	{
		ft_deltab(&env);
		ft_strdel(&line);
		exit(0);
	}
	else if (args[0] && !args[1])
	{
		if (args[0][0] != '-' && (args[0][0] < '0' || args[0][0] > '9'))
			ft_printf("minishell: exit: %s: numeric argument required\n",
					args[0]);
		else
		{
			i = (char)ft_atoi(args[0]);
			ft_deltab(&env);
			ft_strdel(&line);
			exit(i);
		}
	}
	else if (args[1])
		ft_printf("minishell: exit: too many arguments\n");
}
