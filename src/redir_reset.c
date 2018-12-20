/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:23:22 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/20 20:28:25 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "minishell.h"

int		reset_redir(t_command *command)
{
	t_redir	*redir;

	redir = command->redir_list;
	while (redir)
	{
		if (redir->fd_copy[STDIN_FILENO] != -1)
		{
			dup2(redir->fd_copy[STDIN_FILENO], STDIN_FILENO);
			close(redir->fd_copy[STDIN_FILENO]);
		}
		if (redir->fd_copy[STDOUT_FILENO] != -1)
		{
			dup2(redir->fd_copy[STDOUT_FILENO], STDOUT_FILENO);
			close(redir->fd_copy[STDOUT_FILENO]);
		}
		redir = redir->next;
	}
	return (0);
}
