/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:25:00 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/13 19:39:49 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_tty_history_fd(t_shell *shell, t_fd *tty_fd, t_fd *hf_fd)
{
	if (hf_fd)
	{
		shell->used_fd = hf_fd;
		if (tty_fd)
		{
			hf_fd->next = tty_fd;
			tty_fd->next = NULL;
		}
		else
			hf_fd->next = NULL;
	}
	else if (tty_fd)
	{
		shell->used_fd = tty_fd;
		tty_fd->next = NULL;
	}
	else
		shell->used_fd = NULL;
}
