/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:32:02 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 18:34:37 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
			new_str[i] = f(s[i]);
			++i;
		}
		new_str[len] = 0;
	}
	return (new_str);
}
