/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:42:07 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/08 10:51:58 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *res1;
	char *res2;

	if (dst == src || n == 0)
		return (dst);
	res1 = (char *)dst;
	res2 = (char *)src;
	while (--n)
		*res1++ = *res2++;
	*res1 = *res2;
	return (dst);
}
