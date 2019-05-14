/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:42:49 by cvignal           #+#    #+#             */
/*   Updated: 2019/05/14 16:50:31 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "shell.h"

static int	display_reverse(t_fc *cmd, t_shell *shell)
{
	int		i;
	char	**multi_lines;
	int		j;

	if (cmd->i_first < cmd->i_last)
		ft_swap_int(&cmd->i_first, &cmd->i_last);
	i = cmd->i_first;
	while (i >= 0 && i >= cmd->i_last)
	{
		if (!ft_strchr(cmd->flags, 'n'))
			ft_printf("%d", i);
		if (ft_strchr(shell->history->data[i], '\n'))
		{
			if (!(multi_lines = ft_strsplit(shell->history->data[i], "\n")))
				return (1);
			j = 0;
			while (multi_lines[j])
				ft_printf("\t%s\n", multi_lines[j++]);
			ft_deltab(&multi_lines);
		}
		else
			ft_printf("\t%s\n", shell->history->data[i]);
		i--;
	}
	return (0);
}

int			fc_display(t_fc *cmd, t_shell *shell)
{
	int		i;
	char	**multi_lines;
	int		j;

	if (ft_strchr(cmd->flags, 'r'))
		return (display_reverse(cmd, shell));
	i = cmd->i_first;
	while (i < shell->history->length && i <= cmd->i_last)
	{
		if (!ft_strchr(cmd->flags, 'n'))
			ft_printf("%d", i);
		if (ft_strchr(shell->history->data[i], '\n'))
		{
			if (!(multi_lines = ft_strsplit(shell->history->data[i], "\n")))
				return (1);
			j = 0;
			while (multi_lines[j])
				ft_printf("\t%s\n", multi_lines[j++]);
			ft_deltab(&multi_lines);
		}
		else
			ft_printf("\t%s\n", shell->history->data[i]);
		i++;
	}
	return (0);
}
