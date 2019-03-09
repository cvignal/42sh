/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:11:37 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/09 17:20:35 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int	usage_type(void)
{
	ft_dprintf(2, "fc: usage: fc [-lnrs] [-e editor] [old=new] [first [last]]\n");
	return (-1);
}

static int	parse_flags(char *flags, char **args)
{
	int	j;
	int	k;

	j = 1;
	while (args[j] && !ft_strequ(args[j], "--") && args[j][0] == '-')
	{
		k = 1;
		while (args[j][k])
		{
			if (args[j][k] == 'e' || args[j][k] == 'l' || args[j][k] == 'n'
					|| args[j][k] == 's' || args[j][k] == 'r')
			{
				if (!ft_strchr(flags, args[j][k]))
					flags[ft_strlen(flags)] = args[j][k];
			}
			else
			{
				ft_dprintf(2, "%s: fc: -%c: invalid option\n"
						, EXEC_NAME, args[j][k]);
				return (usage_type());
			}
			k++;
		}
		j++;
	}
	return (j + ft_strequ(args[j], "--"));
}

int	fc(t_shell *shell, char **args)
{
	char	flags[6];

	ft_bzero(flags, 6);
	if ((i = parse_flags(flags, args)) == -1)
		return (1);
	return (0);
}
