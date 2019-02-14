/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:51:15 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/14 17:50:21 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;

	len_needle = ft_strlen(needle);
	if (len_needle == 0)
		return ((char *)haystack);
	while (*haystack && len-- >= len_needle)
	{
		if (*haystack == *needle
				&& ft_memcmp(haystack, needle, len_needle) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
