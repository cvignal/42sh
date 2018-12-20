/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 00:47:57 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 11:35:28 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nbr)
{
	int				pow;
	unsigned int	value;

	if (nbr < 0)
	{
		ft_putchar('-');
		value = -nbr;
	}
	else
		value = nbr;
	pow = 1;
	while ((value / pow) > 9)
		pow *= 10;
	while (pow >= 1)
	{
		ft_putchar(value / pow + '0');
		value %= pow;
		pow /= 10;
	}
}
