/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:58:54 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 18:36:44 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new_str;
	unsigned int	pos;
	unsigned int	i;

	new_str = NULL;
	if (s1 && s2)
	{
		new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (new_str)
		{
			pos = 0;
			i = 0;
			while (s1[i])
				new_str[pos++] = s1[i++];
			i = 0;
			while (s2[i])
				new_str[pos++] = s2[i++];
			new_str[pos] = 0;
		}
	}
	return (new_str);
}
