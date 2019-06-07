/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:37:55 by cvignal           #+#    #+#             */
/*   Updated: 2019/05/01 16:21:02 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	size_t				size_ll;
	size_t				size_end;
	size_t				count;

	size_ll = n / sizeof(unsigned long long);
	size_end = n % sizeof(unsigned long long);
	count = 0;
	while (count < size_ll)
		((unsigned long long *)s)[count++] = 0;
	count = 0;
	while (count < size_end)
		((unsigned char *)s)[n - size_end + count++] = 0;
}
