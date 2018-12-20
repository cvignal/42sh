/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 23:55:29 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/08 09:42:30 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		++s1;
		++s2;
		--n;
		if (n <= 0)
			return (0);
	}
	if (n <= 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
