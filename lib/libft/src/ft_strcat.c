/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:05:15 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/19 13:55:24 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strcat(char *s1, const char *s2)
{
	char	*res;

	if (!s1)
		return (NULL);
	res = s1;
	while (*s1)
		s1++;
	while ((*s1++ = *s2++))
		;
	return (res);
}
