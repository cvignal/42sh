/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:50:27 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/02 17:22:06 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "libft.h"
#include "shell.h"
#include "fill_line.h"

void		disable_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void		enable_signal(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
