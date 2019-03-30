/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idx_fc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:00:24 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/30 18:58:12 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int		fc_find_cmd(char *str, t_array *history)
{
	int		i;
	size_t	len;
	int		nb;

	if (!history)
		return (0);
	if (ft_isdigit(str[0]) || str[0] == '-' || str[0] == '+')
	{
		nb = ft_atoi(str);
		if (nb < 0 && history->length + nb >= 0)
			nb += history->length;
		else if (history->length + nb < 0)
			nb = 0;
		return (nb);
	}
	i = history->length - 1;
	len = ft_strlen(str);
	while (i > 0)
	{
		if (ft_strnequ(str, history->data[i], len))
			break ;
		i--;
	}
	return (i);
}

void	fc_index(t_fc *cmd, t_shell *shell)
{
	if (cmd->flags[0] == 's')
	{
		if (cmd->first)
			cmd->i_first = fc_find_cmd(cmd->first, shell->history);
		else
			cmd->i_first = shell->history->length - 1;
	}
	else
	{
		if (cmd->first)
			cmd->i_first = fc_find_cmd(cmd->first, shell->history);
		else
		{
			if (ft_strchr(cmd->flags, 'l'))
				cmd->i_first = shell->history->length >= 15
					? shell->history->length - 15 : 0;
			else
				cmd->i_first = shell->history->length - 1;
		}
		if (cmd->last)
			cmd->i_last = fc_find_cmd(cmd->last, shell->history);
		else
			cmd->i_last = ft_strchr(cmd->flags, 'l') ?
				shell->history->length - 1 : cmd->i_first;
	}
}
