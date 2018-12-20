/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 08:51:25 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 19:02:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] && to_find[j] && str[i + j] == to_find[j]
				&& i + j < len)
			++j;
		if (!to_find[j])
			return ((char *)str + i);
		else
			++i;
	}
	return (!*to_find ? (char *)str : NULL);
}
