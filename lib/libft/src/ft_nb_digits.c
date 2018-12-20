/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:45:35 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/01 16:44:36 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nb_digits(unsigned long long value, int base)
{
	int i;

	i = (value == 0 ? 1 : 0);
	while (value)
	{
		value /= base;
		i++;
	}
	return (i);
}
