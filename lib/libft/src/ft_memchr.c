/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:41:52 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/06 19:13:40 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*buf;
	size_t			i;

	buf = (unsigned char *)s;
	i = 0;
	if (n == 0)
		return (NULL);
	while (n--)
	{
		if (buf[i] == (unsigned char)c)
			return (buf + i);
		i++;
	}
	return (NULL);
}
