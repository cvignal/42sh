/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 15:49:38 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:21:53 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int					ft_len(long double nb)
{
	int i;

	i = (nb < 0);
	(nb <= 0) ? nb *= -1 : 0;
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static unsigned long long	ft_ten_power(int i)
{
	unsigned long long power;

	power = 1;
	while (i >= 0)
	{
		power *= 10;
		i--;
	}
	return (power);
}

static long	long			ft_abs(long nbr)
{
	return ((nbr < 0) ? -nbr : nbr);
}

void						ft_roundup(char *str, long double nb, int precision)
{
	long long	nbr;
	int			prec;
	int			i;
	int			ret;
	char		c;

	i = ft_len(nb);
	nb = nb - (long long)nb;
	nbr = (long long)(nb * ft_ten_power(precision));
	prec = precision;
	ret = (ft_abs(nbr % 10) > 4);
	while (precision >= 0)
	{
		c = '0' + ft_abs(nbr % 10) + ret;
		if (c > '9')
			c = '0';
		else
			ret = 0;
		str[i + precision-- + 2] = c;
		nbr = ft_abs(nbr / 10);
	}
	str[i + prec + 2] = '\0';
}

char						*ft_dtoa(long double nb, int precision)
{
	char		*str;
	int			i;
	int			prec;
	long long	nbr;

	nbr = (long long)nb;
	precision = (precision == -1) ? 6 : precision;
	prec = precision;
	if (!(str = ft_strnew(ft_len(nb) + precision + 1)))
		return (NULL);
	i = ft_len(nb);
	str[i + 1] = (precision == 0) ? '\0' : '.';
	while (i >= 0)
	{
		str[i--] = '0' + ft_abs(nbr % 10);
		nbr = ft_abs(nbr / 10);
	}
	i = ft_len(nb);
	(nb < 0) ? str[0] = '-' : 0;
	ft_roundup(str, nb, prec);
	return (str);
}
