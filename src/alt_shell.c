/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:46:07 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/14 10:54:19 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "fill_line.h"

int	alt_init_shell(t_shell *shell)
{
	shell->history = NULL;
	shell->fd_op = 1;
	g_fd_output = 1;
	return (0);
}
