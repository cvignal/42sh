/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:38:57 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 20:22:46 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char *ret;

	ret = NULL;
	if (!s || !*s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			ret = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		ret = (char *)s;
	return (ret);
}
