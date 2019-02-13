/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_research.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:11:43 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/13 11:34:29 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>

#include "shell.h"
#include "fill_line.h"

int	ft_ctrlr(t_shell *shell)
{
	t_puts("cr");
	t_puts("dl");
	ft_printf("(reverse-i-search)`': ");
	(void)shell;
	return (0);
}
