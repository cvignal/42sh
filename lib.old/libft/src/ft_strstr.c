/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:41:55 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/08 10:44:30 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	n;

	n = ft_strlen(needle);
	if (!ft_strlen(haystack) && !n)
		return ((char *)haystack);
	if (n == 0)
		return ((char *)haystack);
	while (*haystack)
		if (!ft_memcmp(haystack++, needle, n))
			return ((char *)(haystack - 1));
	return (NULL);
}
