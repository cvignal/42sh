/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:45:20 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 12:05:46 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*tmp;
	size_t	i;

	tmp = malloc(n);
	if (tmp)
	{
		i = 0;
		while (i < n)
		{
			tmp[i] = ((char *)src)[i];
			++i;
		}
		i = 0;
		while (i < n)
		{
			((char *)dst)[i] = tmp[i];
			++i;
		}
		free(tmp);
	}
	return (dst);
}
