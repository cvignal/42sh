/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:40:36 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 18:34:53 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	unsigned int	i;
	char			*new_str;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new_str = malloc(len + 1);
	if (new_str)
	{
		i = 0;
		while (i < len)
		{
			new_str[i] = f(i, s[i]);
			++i;
		}
		new_str[i] = 0;
	}
	return (new_str);
}
