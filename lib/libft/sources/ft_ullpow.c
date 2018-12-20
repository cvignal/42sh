/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ullpow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 12:49:13 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/13 12:49:23 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_ullpow(unsigned long long nbr, unsigned long int pow)
{
	unsigned long long	res;

	res = 1;
	while (pow)
	{
		res *= nbr;
		--pow;
	}
	return (res);
}
