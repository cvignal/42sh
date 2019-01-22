/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:35:38 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/22 14:35:31 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_index(size_t *tab)
{
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
}

static int	loop_match(char c, char *str, size_t *pos)
{
	if (c == '?' && pos[1] < ft_strlen(str))
	{
		pos[0]++;
		pos[1]++;
		return (1);
	}
	else if (c == '*')
	{
		pos[2] = pos[0];
		pos[3] = pos[1] + 1;
		pos[0]++;
		return (1);
	}
	else if (pos[1] < ft_strlen(str) && str[pos[1]] == c)
	{
		pos[1]++;
		pos[0]++;
		return (1);
	}
	return (0);
}

int			ft_match(char *pattern, char *str)
{
	size_t	pos[4];

	init_index(pos);
	while (pos[0] < ft_strlen(pattern) || pos[1] < ft_strlen(str))
	{
		if (pos[0] < ft_strlen(pattern))
		{
			if (loop_match(pattern[pos[0]], str, pos))
				continue ;
		}
		if (pos[3] > 0 && pos[3] <= ft_strlen(str))
		{
			pos[0] = pos[2];
			pos[1] = pos[3];
			continue ;
		}
		return (0);
	}
	return (1);
}
