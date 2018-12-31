/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ef.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 17:37:20 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 17:39:47 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "21sh.h"

int	expr_ef(t_shell *shell, char **args)
{
	struct stat	f1;
	struct stat	f2;

	(void)shell;
	if (lstat(args[0], &f1) || lstat(args[0], &f2))
		return (1);
	if (f1.st_dev == f2.st_dev && f1.st_ino == f2.st_ino)
		return (0);
	return (1);
}
