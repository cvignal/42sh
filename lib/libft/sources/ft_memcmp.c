/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:59:09 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 17:37:04 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		++i;
	if (i == len)
		return (0);
	return ((int)(((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]));
}
