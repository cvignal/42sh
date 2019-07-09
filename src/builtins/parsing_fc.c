/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 11:33:36 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/09 15:14:48 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int			usage_fc(int error, char c)
{
	if (!error)
		ft_dprintf(2, "%s: fc: -%c: invalid option or option mix\n"
				, EXEC_NAME, c);
	if (error == 1)
		ft_dprintf(2, "%s: fc: -e: option requires an argument\n"
				, EXEC_NAME);
	ft_dprintf(2, "%s%s%s%s\n", FC_0, FC_1, FC_2, FC_3);
	return (-1);
}

static int	fc_valid_option(char *opt, int i, char *flags)
{
	if (!ft_strchr("relns", opt[i]))
		return (0);
	if (opt[i] == 's' && flags[0] && flags[0] != 's')
		return (0);
	if (opt[i] != 's' && flags[0] == 's')
		return (0);
	if (opt[i] == 'e' && (ft_strchr(flags, 'l') || ft_strchr(flags, 'n')))
		return (0);
	if (opt[i] == 'l' && ft_strchr(flags, 'e'))
		return (0);
	return (1);
}

static int	fc_parse_options(t_fc *cmd, char **args, int i)
{
	if (i > 1 && args[i - 1][0] == '-' && ft_strchr(args[i - 1], 'e'))
	{
		if (!(cmd->editor = ft_strdup(args[i])))
			return (1);
	}
	else if (ft_strchr(args[i], '=') && cmd->flags[0] == 's')
	{
		if (fc_cut_pattern(cmd, args[i]))
			return (1);
	}
	else if (!cmd->first)
	{
		if (!(cmd->first = ft_strdup(args[i])))
			return (1);
	}
	else if (!cmd->last && cmd->first)
	{
		if (!(cmd->last = ft_strdup(args[i])))
			return (1);
	}
	return (0);
}

static int	fc_parse_flags(t_fc *cmd, char **args)
{
	int	i;
	int j;

	i = 1;
	while (args[i] && !ft_strequ(args[i], "--"))
	{
		if (args[i][0] == '-' && ft_isdigit(args[i][1]))
			break ;
		if (args[i][0] == '-')
		{
			j = 1;
			while (args[i][j])
			{
				if (fc_valid_option(args[i], j, cmd->flags))
					cmd->flags[ft_strlen(cmd->flags)] = args[i][j];
				else
					return (usage_fc(0, args[i][j]));
				j++;
			}
		}
		i++;
	}
	return (i + ft_strequ(args[i], "--"));
}

int			fc_init_args(t_fc *cmd, char **args, t_shell *shell)
{
	int	i;
	int	j;

	if ((j = fc_parse_flags(cmd, args)) == -1)
		return (1);
	i = 1;
	while (args[i])
	{
		if (args[i][0] != '-' || i >= j)
		{
			if (fc_parse_options(cmd, args, i))
				return (1);
		}
		i++;
	}
	fc_index(cmd, shell);
	if (cmd->i_last < cmd->i_first && !ft_strchr(cmd->flags, 'r')
			&& cmd->flags[0] != 's')
	{
		ft_swap_int(&cmd->i_last, &cmd->i_first);
		cmd->flags[ft_strlen(cmd->flags)] = 'r';
	}
	return (0);
}
