/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 15:19:28 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/10 15:22:13 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(const char *s1, size_t n)
{
	char	*buf;
	char	*res;
	size_t	len;

	buf = (char *)s1;
	len = n > ft_strlen(s1) ? ft_strlen(s1) : n;
	if (!(res = ft_strnew(len)))
		return (NULL);
	ft_strncpy(res, buf, n);
	return (res);
}
