/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:52:18 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/10 15:21:57 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*buf;
	char	*res;
	size_t	i;

	buf = (char *)s1;
	if (!(res = (char *)malloc(sizeof(char) * ft_strlen(buf) + 1)))
		return (NULL);
	i = 0;
	while (buf[i])
	{
		res[i] = buf[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
