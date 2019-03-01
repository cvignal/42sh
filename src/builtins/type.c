/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 09:49:46 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/01 12:16:28 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	usage_type(void)
{
	ft_dprintf(2, "type: usage: type [-apt] name [name ...]\n");
	return (-1);
}

int			parse_flags(char *flags, char **args)
{
	int	j;
	int	k;

	j = 1;
	while (args[j] && !ft_strequ(args[j], "--") && args[j][0] == '-')
	{
		k = 1;
		while (args[j][k])
		{
			if (args[j][k] == 'a' || args[j][k] == 't' || args[j][k] == 'p')
			{
				if (!ft_strchr(flags, args[j][k]))
					flags[ft_strlen(flags)] = args[j][k];
			}
			else
			{
				ft_dprintf(2, "%s: type: -%c: invalid option\n"
						, EXEC_NAME, args[j][k]);
				return (usage_type());
			}
			k++;
		}
		j++;
	}
	return (j + ft_strequ(args[j], "--"));
}

void		print_norm_type(char **args, int i, char *flags, t_shell *shell)
{
	char	*cmd;

	cmd = NULL;
	while (args[i])
	{
		if (is_builtin(args[i]))
		{
			ft_printf("%s is a shell builtin\n", args[i]);
			if (ft_strchr(flags, 'a') && (cmd = find_command(shell, args[i])))
				ft_printf("%s is %s\n", args[i], cmd);
			if (cmd)
				ft_strdel(&cmd);
		}
		else if (is_a_keyword(args[i]))
			ft_printf("%s is a shell keyword\n", args[i]);
		else if ((cmd = find_command(shell, args[i])))
			ft_printf("%s is %s\n", args[i], cmd);
		else
			ft_dprintf(2, "%s: type: %s: not found\n", EXEC_NAME, args[i]);
		i++;
		if (cmd)
			ft_strdel(&cmd);
	}
}

int			builtin_type(t_shell *shell, char **args)
{
	int		i;
	char	flags[4];

	i = 1;
	ft_bzero(flags, 4);
	if ((i = parse_flags(flags, args)) == -1)
		return (1);
	if (ft_strchr(flags, 'p'))
		print_loc_type(args, i, flags, shell);
	else if (ft_strchr(flags, 't'))
		print_only_type(args, i, flags, shell);
	else
		print_norm_type(args, i, flags, shell);
	return (0);
}
