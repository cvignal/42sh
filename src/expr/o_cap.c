/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_cap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 17:26:09 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 17:28:13 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "21sh.h"

int	expr_o_cap(t_shell *shell, char **args)
{
	uid_t		uid;
	struct stat	st;

	(void)shell;
	if (lstat(args[1], &st))
		return (1);
	uid = getuid();
	if (st.st_uid == uid)
		return (0);
	return (1);
}
