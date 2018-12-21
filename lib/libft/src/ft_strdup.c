/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:52:18 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/21 18:08:53 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*ret;

	len = ft_strlen(s);
	ret = malloc(sizeof(*ret) * (len + 1));
	if (ret)
	{
		i = 0;
		while (i < len)
		{
			ret[i] = s[i];
			++i;
		}
		ret[i] = 0;
	}
	return (ret);
}
