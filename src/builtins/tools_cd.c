/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 19:06:59 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/28 16:23:55 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

static int		usage_cd(char a)
{
	ft_dprintf(2, "%s: cd: %c: invalid option\n", EXEC_NAME, a);
	ft_dprintf(2, "cd: usage: cd [-L|-P] [dir]\n");
	return (-1);
}

unsigned int	cd_parse_options(char **args, int *option)
{
	int	i;
	int j;

	i = 1;
	*option = 0;
	while (args[i] && !ft_strequ(args[i], "--") && !ft_strequ(args[i], "-")
			&& args[i][0] == '-')
	{
		j = 1;
		while (args[i][j])
		{
			if (args[i][j] != 'P' && args[i][j] != 'L')
				return (usage_cd(args[i][j]));
			else if (args[i][j] == 'L')
				*option = 0;
			else if (args[i][j] == 'P')
				*option = 1;
			j++;
		}
		i++;
	}
	return (i + ft_strequ(args[i], "--"));
}

static char		*concat_path(const char *path, const char *bin
		, size_t size_path)
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

char			*cd_parse_path(t_shell *shell, const char *dir)
{
	const char	*path;
	char		*bin_path;
	size_t		size_path;

	if ((path = get_var_value(get_var(shell->exec_vars, "CDPATH"))))
	{
		while (*path)
		{
			size_path = 0;
			while (path[size_path] && path[size_path] != ':')
				++size_path;
			bin_path = concat_path(path, dir, size_path);
			if (!bin_path || (!access(bin_path, F_OK) && (file_type(bin_path)
							== 'd' || file_type(bin_path) == 'l')))
				return (bin_path);
			free(bin_path);
			path += size_path;
			if (*path == ':')
				++path;
		}
	}
	return (ft_strjoin("./", dir));
}
