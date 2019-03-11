/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:11:37 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/11 18:32:32 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void	free_fc(t_fc *cmd)
{
	if (cmd->editor)
		free(cmd->editor);
	if (cmd->first)
		free(cmd->first);
	if (cmd->last)
		free(cmd->last);
	if (cmd->pattern)
		free(cmd->pattern);
}

void	fc_exec_cmd(t_fc *cmd, t_shell *shell)
{
	(void)cmd;
	(void)shell;
}

void	fc_display(t_fc *cmd, t_shell *shell)
{
	int	i;

	i = cmd->i_first;
	while (i < shell->history->length && i < cmd->i_last)
	{
		if (!ft_strchr(cmd->flags, 'n'))
			ft_printf("%d", i);
		ft_printf("\t%s\n", i, shell->history->data[i]);
		i++;
	}
}

int		builtin_fc(t_shell *shell, char **args)
{
	t_fc	cmd;

	ft_bzero(&cmd, sizeof(cmd));
	if (fc_init_args(&cmd, args, shell))
	{
		free_fc(&cmd);
		return (1);
	}
	if (cmd.flags[0] == 's')
		fc_exec_cmd(&cmd, shell);
	else
		fc_display(&cmd, shell);
	free_fc(&cmd);
	return (0);
}
