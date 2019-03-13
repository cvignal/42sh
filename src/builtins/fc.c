/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:11:37 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/13 17:02:47 by cvignal          ###   ########.fr       */
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
	if (cmd->old_p)
	{
		free(cmd->old_p);
		free(cmd->new_p);
	}
}

int		fc_exec_cmd(t_fc *cmd, t_shell *shell)
{
	size_t	len;
	char	*cpy;

	len = ft_strlen(shell->history->data[cmd->i_first]);
	if (cmd->old_p && cmd->new_p)
		len += ft_imax(0, ft_strlen(cmd->new_p) - ft_strlen(cmd->old_p));
	if (!(cpy = ft_strnew(len)))
		return (1);
	if (cmd->old_p)
		ft_replace_str(cpy, shell->history->data[cmd->i_first],
				cmd->old_p, cmd->new_p);
	else
		ft_strcpy(cpy, shell->history->data[cmd->i_first]);
	free(cpy);
	return (0);
}

int		fc_display(t_fc *cmd, t_shell *shell)
{
	int		i;
	char	**multi_lines;
	int		j;

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

int		fc_edit(t_fc *cmd, t_shell *shell)
{
	t_tmpfile	file;

	if (fc_open_file(cmd, shell, &file))
		return (1);
	return (0);
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
	else if (ft_strchr(cmd.flags, 'l'))
		fc_display(&cmd, shell);
	else
		fc_edit(&cmd, shell);
	free_fc(&cmd);
	return (0);
}
