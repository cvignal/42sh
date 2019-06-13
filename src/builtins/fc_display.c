/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:07:39 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/13 16:31:42 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int	fc_display_reverse(t_fc *cmd, t_shell *shell)
{
	int		i;

	i = cmd->i_last;
	while (i > 0 && i >= cmd->i_first)
	{
		if (!ft_strchr(cmd->flags, 'n'))
			ft_printf("%d", i);
		if (ft_strchr(shell->history->data[i], '\n'))
		{
			if (fc_display_multi(shell->history->data[i]))
				return (1);
		}
		else
			ft_printf("\t%s\n", shell->history->data[i]);
		i--;
	}
	return (0);
}

int	fc_display_multi(char *str)
{
	char	**multi_lines;
	int		j;

	if (!(multi_lines = ft_strsplit(str, "\n")))
		return (1);
	j = 0;
	while (multi_lines[j])
		ft_printf("\t%s\n", multi_lines[j++]);
	ft_deltab(&multi_lines);
	return (0);
}
