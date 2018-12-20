/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:39:14 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/12 16:41:00 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr(unsigned int nbr)
{
	unsigned int	pow;

	pow = 1;
	while ((nbr / pow) > 9)
		pow *= 10;
	while (pow >= 1)
	{
		ft_putchar(nbr / pow + '0');
		nbr %= pow;
		pow /= 10;
	}
}
