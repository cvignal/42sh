/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 17:29:47 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 17:32:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "21sh.h"
#include "libft.h"

int	expr_s_cap(t_shell *shell, char **args)
{
	(void)shell;
	if (access(args[1], F_OK))
		return (1);
	if (file_type(args[1]) == 's')
		return (0);
	return (1);
}
