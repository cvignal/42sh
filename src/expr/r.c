/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:15:01 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 16:26:26 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "21sh.h"

int	expr_r(t_shell *shell, char **args)
{
	(void)shell;
	if (access(args[1], R_OK))
		return (1);
	return (0);
}
