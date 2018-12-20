/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:55:35 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 18:36:17 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*new_str;
	unsigned int	i;

	if (!s)
		return (NULL);
	new_str = malloc(len + 1);
	if (new_str)
	{
		i = 0;
		while (i < len)
		{
			new_str[i] = s[start + i];
			++i;
		}
		new_str[i] = 0;
	}
	return (new_str);
}
