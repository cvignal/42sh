/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:48:24 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/08 15:03:11 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *res;

	if ((int)len < 0 || !s)
		return (NULL);
	while (start--)
		s++;
	if (!(res = ft_strnew(len)))
		return (NULL);
	res = ft_strncpy(res, s, len);
	return (res);
}
