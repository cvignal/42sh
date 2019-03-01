/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 11:32:04 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/01 12:18:04 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

void	print_only_type(char **args, int i, char *flags, t_shell *shell)
{
	char	*cmd;

	cmd = NULL;
	while (args[i])
	{
		if (is_builtin(args[i]))
		{
			ft_printf("builtin\n");
			if (ft_strchr(flags, 'a') && (cmd = find_command(shell, args[i])))
				ft_printf("file\n");
			if (cmd)
				ft_strdel(&cmd);
		}
		else if ((cmd = find_command(shell, args[i])))
			ft_printf("file\n");
		else if (is_a_keyword(args[i]))
			ft_printf("keyword\n");
		if (cmd)
			ft_strdel(&cmd);
		i++;
	}
}

void	print_loc_type(char **args, int i, char *flags, t_shell *shell)
{
	char	*cmd;

	cmd = NULL;
	while (args[i])
	{
		if (is_builtin(args[i]))
		{
			if (ft_strchr(flags, 'a') && (cmd = find_command(shell, args[i])))
				ft_printf("%s\n", cmd);
			if (cmd)
				ft_strdel(&cmd);
		}
		else if ((cmd = find_command(shell, args[i])))
			ft_printf("%s\n", cmd);
		if (cmd)
			ft_strdel(&cmd);
		i++;
	}
}
