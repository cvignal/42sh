/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:32:16 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 20:21:55 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	if (!s || !*s)
		return (NULL);
	while (*s != (char)c)
	{
		if (!*(s + 1))
			return (NULL);
		s++;
	}
	return ((char *)s);
}
