/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:48:26 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:15:29 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*res1;
	unsigned char	*res2;
	size_t			i;

	if ((n == 0 && c) || dst == src)
		return (NULL);
	res1 = (unsigned char *)dst;
	res2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		res1[i] = res2[i];
		if (res1[i] == (unsigned char)c)
			return (dst + 1 + i);
		i++;
	}
	return (NULL);
}
