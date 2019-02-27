/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_cut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:56:31 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/27 16:00:02 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "fill_line.h"

int	vm_cut(t_shell *shell)
{
	if (vm_copy(shell) == -1)
		return (1);
	if (shell->line.cursor > shell->line.select_curs)
	{
		while (shell->line.cursor >= shell->line.select_curs)
			ft_backspace(shell);
	}
	else
	{
		while (shell->line.cursor <= shell->line.select_curs)
		{
			ft_delete(shell);
			shell->line.select_curs--;
		}
	}
	return (1);
}
