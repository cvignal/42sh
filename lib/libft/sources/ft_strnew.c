/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:20:41 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 09:23:58 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	str = malloc(size + 1);
	if (str)
	{
		str[size] = 0;
		while (size)
			str[--size] = 0;
	}
	return (str);
}
