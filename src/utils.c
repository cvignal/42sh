/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:03:28 by agrouard          #+#    #+#             */
/*   Updated: 2019/04/22 19:39:29 by agrouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int	fail(char *proc, char *err, char *message, int ret)
{
	if (err)
		ft_dprintf(2, "%s: %s: %s\n", proc, err, message);
	else
		ft_dprintf(2, "%s: %s\n", proc, message);
	return (ret);
}

int	do_error_handling(char *name)
{
	struct stat info;

	if (access(name, F_OK) == 0)
	{
		if (stat(name, &info) != -1 && S_ISDIR(info.st_mode))
			return (fail(EXEC_NAME, name, "Is a directory", 126));
		else if (access(name, X_OK) == -1)
			return (fail(EXEC_NAME, name, "Permission denied", 126));
		else
			return (fail(EXEC_NAME, name, "Unexpected error", 127));
	}
	if (ft_strchr(name, '/') != NULL)
		return (fail(EXEC_NAME, name, "No such file or directory", 127));
	return (fail(EXEC_NAME, name, "Command not found", 127));
}

char	*ft_strcjoin(char const *s1, const char c, char const *s2)
{
	unsigned int	i;
	char			*join;

	if (!s1 || !s2)
		return (NULL);
	if (!(join = ft_strnew(ft_strlen(s1) + 1 + ft_strlen(s2))))
		return (NULL);
	i = 0;
	while (*s1)
		join[i++] = *s1++;
	join[i++] = c;
	while (*s2)
		join[i++] = *s2++;
	join[i] = 0;
	return (join);
}

char	*ft_strcjoin_free(char *s1, const char c, char *s2, int flag)
{
	char *res;

	res = ft_strcjoin(s1, c, s2);
	if (flag & 1)
		free(s1);
	if (flag & 2)
		free(s2);
	return (res);
}
