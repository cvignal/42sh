/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 11:06:51 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/11 17:42:42 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int			usage_fc(void)
{
	ft_dprintf(2, "%s\n", FC_USAGE_MESSAGE);
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
	else if (ft_strchr(args[i], '='))
	{
		if (!(cmd->pattern = ft_strdup(args[i])))
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
		if (args[i][0] == '-')
		{
			j = 1;
			while (args[i][j])
			{
				if (fc_valid_option(args[i], j, cmd->flags))
					cmd->flags[ft_strlen(cmd->flags)] = args[i][j];
				else
				{
					ft_dprintf(2, "%s: fc: -%c: invalid option or option mix\n"
							, EXEC_NAME, args[i][j]);
					return (usage_fc());
				}
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
	if (cmd->i_last < cmd->i_first && !ft_strchr(cmd->flags, 'r'))
	{
		ft_swap_int(&cmd->i_last, &cmd->i_first);
		cmd->flags[ft_strlen(cmd->flags)] = 'r';
	}
	return (0);
}
