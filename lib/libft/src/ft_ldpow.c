/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldpow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 10:32:42 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/14 10:56:22 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double	ft_ldpow(long double nbr, unsigned long int pow)
{
	long double	res;

	res = 1;
	while (pow)
	{
		res *= nbr;
		--pow;
	}
	return (res);
}
