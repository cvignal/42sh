/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:26:03 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/13 12:56:36 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nbr_size_base(int nb, int base)
{
	size_t	size;

	size = 0;
	if (!nb)
		return (1);
	while (nb)
	{
		nb /= base;
		++size;
	}
	return (size);
}

size_t			ft_putnbr_base(int nb, const char *base)
{
	size_t				size;
	size_t				base_len;
	unsigned long int	pow;
	int					sign;
	size_t				ret;

	base_len = ft_strlen(base);
	size = get_nbr_size_base(nb, base_len);
	if (nb < 0)
	{
		sign = -1;
		ft_putchar('-');
	}
	else
		sign = 1;
	ret = size + ((sign == -1) ? 1 : 0);
	while (size--)
	{
		pow = ft_ullpow(base_len, size);
		ft_putchar(*(base + (nb / pow) * sign));
		nb %= pow;
	}
	return (ret);
}
