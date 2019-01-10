/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:28:56 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 13:30:41 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "shell.h"
#include "libft.h"

int	expr_h(t_shell *shell, char **args)
{
	(void)shell;
	if (access(args[1], F_OK))
		return (1);
	if (file_type(args[1]) == 'l')
		return (0);
	return (1);
}
