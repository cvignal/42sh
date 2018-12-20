/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:57:04 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/10 10:56:11 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strcpy(char *dst, const char *src)
{
	char	*buf;
	size_t	i;

	i = 0;
	if (!src)
		return (dst);
	buf = (char *)src;
	while (buf[i])
	{
		dst[i] = buf[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
