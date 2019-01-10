/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:38:22 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 16:42:43 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "shell.h"

int	expr_s(t_shell *shell, char **args)
{
	struct stat	st;

	(void)shell;
	if (lstat(args[1], &st))
		return (1);
	if (st.st_size > 0)
		return (0);
	return (1);
}
