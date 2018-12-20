/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segfault.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:27:36 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/11 16:56:13 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

void	check_segfault(char *prog, int status)
{
	if (WTERMSIG(status) == SIGSEGV)
		ft_printf("[1]\tSegfault %s\n", prog);
	else if (WTERMSIG(status) == SIGBUS)
		ft_printf("[1]\tBus error %s\n", prog);
	else if (WTERMSIG(status) == SIGFPE)
		ft_printf("[1]\tFloating point exception %s\n", prog);
}
