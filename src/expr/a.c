/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 12:43:08 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 12:46:13 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "21sh.h"

int	expr_a(t_shell *shell, char **args)
{
	(void)shell;
	if (access(args[1], F_OK))
		return (1);
	return (0);
}
