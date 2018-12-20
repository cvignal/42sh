/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 16:07:48 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 17:40:09 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

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
