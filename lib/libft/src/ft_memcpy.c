/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:42:07 by cvignal           #+#    #+#             */
/*   Updated: 2019/05/01 16:32:27 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	size_t	n_ll;
	size_t	n_end;

	n_ll = n / sizeof(unsigned long long);
	n_end = n % sizeof(unsigned long long);
	i = 0;
	while (i < n_ll)
	{
		((unsigned long long *)dst)[i] = ((unsigned long long *)src)[i];
		++i;
	}
	i = 0;
	while (i < n_end)
	{
		((unsigned char *)dst)[n - n_end + i] =\
					((unsigned char *)src)[n - n_end + i];
		++i;
	}
	return (dst);
}
