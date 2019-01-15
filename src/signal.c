/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:50:27 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/15 14:07:01 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "libft.h"
#include "shell.h"

void	print_newline(int i)
{
	(void)i;
	ft_printf("\n");
}

void	print_prompt(int i)
{
	(void)i;
	ft_printf("\n%s ", PROMPT);
}

void	disable_signal(t_shell *shell)
{
	(void)shell;
	signal(SIGINT, print_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	enable_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ignore_signal(void)
{
	signal(SIGINT, print_newline);
	signal(SIGQUIT, print_newline);
}
