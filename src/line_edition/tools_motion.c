/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_motion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:28:55 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/13 11:36:10 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>

#include "libft.h"
#include "fill_line.h"
#include "shell.h"

size_t	length_prev_line(t_shell *shell)
{
	size_t	ret;
	size_t	j;
	int		k;

	j = 0;
	ret = 0;
	k = 0;
	while (shell->line.cursor > 0 && j < shell->line.cursor - 1)
	{
		j++;
		ret++;
		if (shell->line.data[j] == '\n')
		{
			ret = 0;
			k++;
		}
	}
	if (!k)
		ret += 4;
	return (ret);
}

size_t	length_curr_line(t_shell *shell)
{
	size_t	ret;
	size_t	j;

	j = shell->line.cursor + 1;
	ret = 0;
	if (shell->line.data[j] == '\n')
		return (0);
	while (j < shell->line.len)
	{
		j++;
		ret++;
		if (shell->line.data[j] == '\n')
			break ;
	}
	return (ret);
}

void	clean_under_line(t_shell *shell)
{
	t_puts("sc");
	if (shell)
	{
		while (shell->line.cursor < shell->line.len)
			ft_rightkey(shell);
	}
	t_puts("cd");
	if (!shell)
		t_puts("rc");
}
