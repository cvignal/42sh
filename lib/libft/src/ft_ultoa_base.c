/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:08:49 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:21:36 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	recur_ultoa_b(unsigned long long nb, int base, char *ptr, int index)
{
	char str[17];

	ft_strcpy(str, "0123456789abcdef");
	if (nb >= (unsigned long long)base)
	{
		index = recur_ultoa_b(nb / base, base, ptr, index);
		index = recur_ultoa_b(nb % base, base, ptr, index);
	}
	else
	{
		ptr[index] = str[nb];
		index++;
	}
	return (index);
}

char		*ft_ultoa_base(unsigned long long nb, int base)
{
	char	*ptr;
	int		index;

	if (!(ptr = ft_strnew(ft_nb_digits(nb, base))))
		return (NULL);
	index = 0;
	recur_ultoa_b(nb, base, ptr, index);
	return (ptr);
}
