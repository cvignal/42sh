/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 12:24:57 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 17:35:28 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n)
	{
		*((unsigned char *)dst) = *((unsigned char *)src);
		++dst;
		if (*((unsigned char *)src) == (unsigned char)c)
			return (dst);
		++src;
		--n;
	}
	return (NULL);
}
