/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:18:48 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/24 22:25:12 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vswap(void *a, void *b, size_t content_size)
{
	int	i;

	if (a == b)
		return ;
	i = -1;
	if (content_size == sizeof(int))
	{
		*((int *)a) = *((int *)a) ^ *((int *)b);
		*((int *)b) = *((int *)b) ^ *((int *)a);
		*((int *)a) = *((int *)a) ^ *((int *)b);
	}
	else if (content_size == sizeof(long long))
	{
		*((long long *)a) = *((long long *)a) ^ *((long long *)b);
		*((long long *)b) = *((long long *)b) ^ *((long long *)a);
		*((long long *)a) = *((long long *)a) ^ *((long long *)b);
	}
	else
		while (++i < (int)content_size)
		{
			((unsigned char *)a)[i] = ((unsigned char *)a)[i]
				^ ((unsigned char *)b)[i];
			((unsigned char *)b)[i] = ((unsigned char *)b)[i]
				^ ((unsigned char *)a)[i];
			((unsigned char *)a)[i] = ((unsigned char *)a)[i]
				^ ((unsigned char *)b)[i];
		}
}
