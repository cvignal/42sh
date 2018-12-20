/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrai <gdrai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 10:45:06 by gdrai             #+#    #+#             */
/*   Updated: 2018/12/19 16:21:18 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	recur_ltoa_b(unsigned long long nb, int base, char *ptr, int index)
{
	char	str[17];

	ft_strcpy(str, "0123456789abcdef");
	if (nb >= (unsigned long long)base)
	{
		index = recur_ltoa_b(nb / base, base, ptr, index);
		index = recur_ltoa_b(nb % base, base, ptr, index);
	}
	else
	{
		ptr[index] = str[nb];
		index++;
	}
	return (index);
}

char		*ft_ltoa_base(long long nb, int base)
{
	unsigned long long	i;
	char				*ptr;
	int					index;

	i = nb;
	if (!(ptr = ft_strnew(ft_nb_digits(nb, base) + (nb < 0))))
		return (NULL);
	index = 0;
	if (nb < 0 && base == 10)
	{
		ptr[index++] = '-';
		i = -nb;
	}
	recur_ltoa_b(i, base, ptr, index);
	return (ptr);
}

static int	recur_stoa_b(unsigned short nb, int base, char *ptr, int index)
{
	char	str[17];

	ft_strcpy(str, "0123456789abcdef");
	if (nb >= (unsigned short)base)
	{
		index = recur_stoa_b(nb / base, base, ptr, index);
		index = recur_stoa_b(nb % base, base, ptr, index);
	}
	else
	{
		ptr[index] = str[nb];
		index++;
	}
	return (index);
}

char		*ft_stoa_base(short nb, int base)
{
	unsigned short	i;
	char			*ptr;
	int				index;

	i = nb;
	if (!(ptr = ft_strnew(ft_nb_digits(nb, base))))
		return (NULL);
	index = 0;
	if (nb < 0 && base == 10)
	{
		ptr[index++] = '-';
		i = -nb;
	}
	recur_stoa_b(i, base, ptr, index);
	return (ptr);
}
