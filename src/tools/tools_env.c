/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 10:21:01 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 18:30:19 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int		len_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_free_path_and_prog(char **paths, char *prog)
{
	ft_strdel(&prog);
	ft_deltab(&paths);
}

char	**copy_env(const char **env)
{
	char	**my_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (!(my_env = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!(my_env[i] = ft_strnew(ft_strlen(env[i]))))
			return (NULL);
		ft_strcpy(my_env[i], env[i]);
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}

char	*ft_getenv(char **my_env, char *elem)
{
	int	i;
	int	len;

	i = 0;
	len = (int)ft_strlen(elem);
	while (!ft_strnequ(my_env[i], elem, len))
		i++;
	if (!my_env[i] || !ft_strchr(my_env[i], '='))
		return (NULL);
	return (ft_strchr(my_env[i], '=') + 1);
}

int		add_path(char **args, char **my_env)
{
	char	**paths;
	int		i;
	char	*prog;

	if (!access(args[0], X_OK) && ft_strchr(args[0], '/'))
		return (1);
	if (!(paths = ft_strsplit(ft_getenv(my_env, "PATH"), ":")) || !*paths)
		return (0);
	i = -1;
	prog = ft_strjoin("/", args[0]);
	while (paths[++i])
	{
		prog = ft_strjoin_free(paths[i], prog, 2);
		if (!access(prog, F_OK))
		{
			free(args[0]);
			args[0] = ft_strdup(prog);
			ft_free_path_and_prog(paths, prog);
			return (1);
		}
		ft_strdel(&prog);
		prog = ft_strjoin_free("/", args[0], 0);
	}
	ft_free_path_and_prog(paths, prog);
	return (0);
}
