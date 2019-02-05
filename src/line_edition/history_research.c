/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_research.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:11:43 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/30 18:46:30 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>

#include "shell.h"
#include "fill_line.h"

int	ft_ctrlr(t_shell *shell)
{
	tputs(tgetstr("cr", NULL), 0, ft_printchar);
	tputs(tgetstr("dl", NULL), 0, ft_printchar);
	ft_printf("(reverse-i-search)`': ");
	(void)shell;
	return (0);
}
