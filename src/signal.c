/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:50:27 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/16 17:04:10 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "libft.h"
#include "shell.h"
#include "fill_line.h"

static void	print_newline(int i)
{
	(void)i;
	ft_dprintf(g_fd_output, "\n");
}

void		disable_signal(void)
{
	signal(SIGQUIT, print_newline);
	signal(SIGINT, print_newline);
}

void		enable_signal(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void		ignore_signal(void)
{
	signal(SIGINT, print_newline);
	signal(SIGQUIT, SIG_DFL);
}
