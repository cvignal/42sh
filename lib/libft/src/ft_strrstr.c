/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 17:06:07 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/20 17:08:00 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strrstr(const char *haystack, const char *needle)
{
	size_t	n;
	char	*ret;
	
	ret = NULL;
	n = ft_strlen(needle);
	if (!ft_strlen(haystack) && !n)
		return ((char *)haystack);
	if (n == 0)
		return ((char *)haystack);
	while (*haystack)
		if (!ft_memcmp(haystack++, needle, n))
			ret = (char *)(haystack - 1);
	return (ret);
}
