/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:35:36 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 11:36:21 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nbr, int fd)
{
	int				pow;
	unsigned int	value;

	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		value = -nbr;
	}
	else
		value = nbr;
	pow = 1;
	while ((value / pow) > 9)
		pow *= 10;
	while (pow >= 1)
	{
		ft_putchar_fd(value / pow + '0', fd);
		value %= pow;
		pow /= 10;
	}
}
