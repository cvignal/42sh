/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:51:15 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 16:52:08 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "shell.h"

int	expr_w(t_shell *shell, char **args)
{
	(void)shell;
	if (access(args[1], W_OK))
		return (1);
	return (0);
}
