/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:31:26 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/06 18:18:09 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*res;

	if (len == 0)
		return (b);
	res = (unsigned char *)b;
	while (len--)
	{
		*res = (unsigned char)c;
		if (len)
			res++;
	}
	return (b);
}
