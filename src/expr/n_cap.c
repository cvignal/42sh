/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_cap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 17:17:09 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 18:07:04 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "21sh.h"

int	expr_n_cap(t_shell *shell, char **args)
{
	struct stat	st;

	(void)shell;
	if (lstat(args[1], &st))
		return (1);
	if (st.st_mtim.tv_sec > st.st_atim.tv_sec)
		return (0);
	return (1);
}
