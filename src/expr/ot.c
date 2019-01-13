/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 19:24:07 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/11 18:40:40 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "shell.h"

int	expr_ot(t_shell *shell, char **args)
{
	struct stat	f1;
	struct stat	f2;

	(void)shell;
	if (lstat(args[0], &f1))
		return (1);
	if (lstat(args[2], &f2))
		return (0);
	if (f1.st_mtime < f2.st_mtime)
		return (0);
	return (1);
}
