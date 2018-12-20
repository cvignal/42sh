/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:36:16 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/10 06:26:08 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_bzero(void *mem, size_t len)
{
	unsigned long long	*mem_ptr;
	size_t				eight_len;

	mem_ptr = mem;
	eight_len = len / sizeof(unsigned long long);
	len %= sizeof(unsigned long long);
	while (eight_len)
	{
		*mem_ptr++ = 0;
		--eight_len;
	}
	while (len)
	{
		*((char *)mem++) = 0;
		--len;
	}
}
