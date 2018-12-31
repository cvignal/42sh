/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:36:00 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 13:37:18 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "21sh.h"
#include "libft.h"

int	expr_p(t_shell *shell, char **args)
{
	(void)shell;
	if (access(args[1], F_OK))
		return (1);
	if (file_type(args[1]) == 'p')
		return (0);
	return (1);
}
