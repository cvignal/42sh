/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:52:30 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 16:53:13 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "shell.h"

int	expr_x(t_shell *shell, char **args)
{
	(void)shell;
	if (access(args[1], X_OK))
		return (1);
	return (0);
}
