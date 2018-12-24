/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:51:24 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/24 16:27:08 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

char	file_type(char *path)
{
	struct stat info;

	lstat(path, &info);
	if (S_ISREG(info.st_mode))
		return (info.st_mode & S_IXUSR ? 'x' : '-');
	else if (S_ISDIR(info.st_mode))
		return ('d');
	else if (S_ISCHR(info.st_mode))
		return ('c');
	else if (S_ISBLK(info.st_mode))
		return ('b');
	else if (S_ISFIFO(info.st_mode))
		return ('p');
	else if (S_ISLNK(info.st_mode))
		return ('l');
	else if (S_ISSOCK(info.st_mode))
		return ('s');
	else
		return ('?');
}
