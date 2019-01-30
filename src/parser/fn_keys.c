/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 16:24:09 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/30 11:23:55 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>

#include "fill_line.h"
#include "shell.h"
#include "libft.h"

int	ft_nextword(t_shell *shell)
{
	size_t	i;

	i = shell->line.cursor;
	if (shell->line.cursor < shell->line.len)
	{
		while (shell->line.data[i] != ' ' && i < shell->line.len)
		{
			ft_rightkey(shell);
			i++;
		}
		while (shell->line.data[i] == ' ' && i < shell->line.len)
		{
			ft_rightkey(shell);
			i++;
		}
	}
	return (0);
}

int	ft_prevword(t_shell *shell)
{
	size_t	i;

	i = shell->line.cursor;
	if (shell->line.cursor > 0)
	{
		while (shell->line.data[i] != ' ' && i > 0)
		{
			ft_leftkey(shell);
			i--;
		}
		while (shell->line.data[i] == ' ' && i > 0)
		{
			ft_leftkey(shell);
			i--;
		}
		while (shell->line.data[i] != ' ' && i > 0)
		{
			ft_leftkey(shell);
			i--;
		}
		if (shell->line.cursor > 0)
			ft_rightkey(shell);
	}
	return (0);
}

int	ft_ctrld(t_shell *shell)
{
	char *args[2];

	args[0] = "0";
	args[1] = NULL;
	if (!shell->ctrld && shell->line.len == 0)
		builtin_exit(shell, args);
	if (shell->line.len == 0)
		shell->end_heredoc = 1;
	return (shell->end_heredoc);
}

int	ft_ctrlc(t_shell *shell)
{
	ft_printf("\n$> ");
	free_line(&shell->line);
	return (0);
}

int	ft_ctrll(t_shell *shell)
{
	tputs(tgetstr("cl", NULL), 0, ft_printchar);
	if (shell->line.len)
		ft_printf("$> %s", shell->line.data);
	else
		ft_printf("$> ");
	return (0);
}
