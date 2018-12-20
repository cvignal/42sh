/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:46:54 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/17 17:09:22 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>
#include "minishell.h"

void	print_prompt(int i)
{
	(void)i;
	ft_printf("\n%sMYSHELL%s%s$>%s ", "\e[1;36m",
						"\e[0m", "\e[1;31m", "\e[0m");
}

void	print_newline(int i)
{
	(void)i;
	ft_printf("\n");
}

void	disable_signal(void)
{
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
