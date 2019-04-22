/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_cap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 17:17:09 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/22 15:13:10 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "shell.h"

int	expr_n_cap(t_shell *shell, char **args)
{
	struct stat	st;

	(void)shell;
	if (lstat(args[1], &st))
		return (1);
	if (st.st_mtime > st.st_atime)
		return (0);
	return (1);
}
