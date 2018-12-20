/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:39:45 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/10 06:40:38 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t						i;
	size_t						eight_len;
	unsigned long long			*dst_ptr;
	const unsigned long long	*src_ptr;

	i = 0;
	eight_len = n / sizeof(unsigned long long);
	dst_ptr = dst;
	src_ptr = src;
	while (i < eight_len)
	{
		dst_ptr[i] = src_ptr[i];
		++i;
	}
	i *= sizeof(unsigned long long);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		++i;
	}
	return (dst);
}
