/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:15:24 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 07:30:18 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "shell.h"
#include "libft.h"

static char			*concat_path(const char *path, const char *bin,
		size_t size_path)
{
	size_t		size_bin;
	char		*ret;

	size_path = 0;
	while (path[size_path] && path[size_path] != ':')
		++size_path;
	size_bin = ft_strlen(bin);
	ret = malloc(sizeof(*ret) * (size_path + size_bin + 2));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, path, size_path);
	ret[size_path] = '/';
	ft_memcpy(ret + size_path + 1, bin, size_bin);
	ret[size_path + size_bin + 1] = 0;
	return (ret);
}

static char			*get_local_exec(const char *path)
{
	struct stat	st;

	if (stat(path, &st) || access(path, X_OK))
		return (NULL);
	if (!(st.st_mode & S_IFREG))
		return (NULL);
	return (ft_strdup(path));
}

static const char	*get_path(t_var *vars)
{
	t_var	*path;

	path = get_var(vars, "PATH");
	if (path)
		return (path->var + 5);
	return (NULL);
}

char				*find_command(t_var *vars, const char *command)
{
	const char	*path;
	char		*bin_path;
	size_t		size_path;

	if (!command || !*command)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (get_local_exec(command));
	if ((path = get_path(vars)))
	{
		while (*path)
		{
			size_path = 0;
			while (path[size_path] && path[size_path] != ':')
				++size_path;
			bin_path = concat_path(path, command, size_path);
			if (!bin_path || !access(bin_path, X_OK))
				return (bin_path);
			free(bin_path);
			path += size_path;
			if (*path == ':')
				++path;
		}
	}
	return (NULL);
}
