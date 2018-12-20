/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:08:59 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/06 11:15:20 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*res;

	res = s1;
	while (*s1)
		s1++;
	while (n--)
		if (!(*s1++ = *s2++))
			return (res);
	*s1 = '\0';
	return (res);
}
