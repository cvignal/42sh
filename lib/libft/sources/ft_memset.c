/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:30:28 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/05 15:57:50 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *mem, int c, size_t len)
{
	char	*i;

	i = mem;
	while (len)
	{
		*((char *)i++) = (unsigned char)c;
		--len;
	}
	return (mem);
}
