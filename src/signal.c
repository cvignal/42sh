/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:50:27 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/15 16:49:58 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "libft.h"
#include "shell.h"


static void	print_newline(int i)
{
	(void)i;
	ft_printf("\n");
}

static void	print_prompt(int i)
{
	(void)i;
	ft_printf("\n%s ", PROMPT);
}

void		disable_signal(void)
{
	signal(SIGINT, print_prompt);
}

void		enable_signal(void)
{
	signal(SIGINT, SIG_DFL);
}

void		ignore_signal(void)
{
	signal(SIGINT, print_newline);
}
