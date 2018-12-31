/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 12:49:38 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 12:50:59 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "21sh.h"
#include "libft.h"

int	expr_b(t_shell *shell, char **args)
{
	(void)shell;
	if (access(args[1], F_OK))
		return (1);
	if (file_type(args[1]) == 'b')
		return (0);
	return (1);
}
