/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:00:07 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/07 13:19:36 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*buf1;
	char	*buf2;
	size_t	i;

	if (len == 0)
		return (dst);
	buf1 = (char *)dst;
	buf2 = (char *)src;
	i = -1;
	if (buf2 < buf1)
		while ((int)(--len) >= 0)
			buf1[len] = buf2[len];
	else
		while (++i < len)
			buf1[i] = buf2[i];
	return (dst);
}
