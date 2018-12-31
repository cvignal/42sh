/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:32:23 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 13:34:45 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "21sh.h"
#include "libft.h"

int	expr_k(t_shell *shell, char **args)
{
	struct stat	st;

	(void)shell;
	if (access(args[1], F_OK))
		return (1);
	if (lstat(args[1], &st))
		return (1);
	if (st.st_mode & S_ISVTX)
		return (0);
	return (1);
}
