/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:45:24 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/06 20:03:14 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*buf1;
	char	*buf2;

	if (n == 0)
		return (0);
	buf1 = (char *)s1;
	buf2 = (char *)s2;
	while (--n && *buf1 == *buf2)
	{
		buf1++;
		buf2++;
	}
	return ((unsigned char)(*buf1) - (unsigned char)(*buf2));
}
