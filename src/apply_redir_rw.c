/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir_rw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 01:27:07 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/12 02:28:42 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "ast.h"
#include "libft.h"

int	apply_redir_rw(t_redir *redir)
{
	if (dup2(redir->fd, redir->in) == -1)
	{
		ft_dprintf(2, "%s: unable to create redirection\n", EXEC_NAME);
		return (1);
	}
	return (0);
}
