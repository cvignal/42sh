/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:54:51 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 17:13:22 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "21sh.h"

int	expr_g_cap(t_shell *shell, char **args)
{
	struct stat	st;
	gid_t		gid;

	(void)shell;
	if (lstat(args[1], &st))
		return (1);
	gid = getgid();
	if (st.st_gid == gid)
		return (0);
	return (1);
}
