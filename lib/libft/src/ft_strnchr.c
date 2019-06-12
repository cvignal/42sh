/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:55:31 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/12 15:59:29 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *s, int c, size_t len)
{
	size_t	i;
	char	*cpy;

	i = 0;
	cpy = (char *)s;
	while (cpy[i] && i < len)
	{
		if (cpy[i] == c)
			return (cpy + i);
		i++;
	}
	return (NULL);
}
