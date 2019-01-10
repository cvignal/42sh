/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:18:38 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 13:20:30 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "shell.h"

int	expr_f(t_shell *shell, char **args)
{
	char	c;

	(void)shell;
	if (access(args[1], F_OK))
		return (1);
	c = file_type(args[1]);
	if (c == '-' || c == 'x')
		return (0);
	return (1);
}
