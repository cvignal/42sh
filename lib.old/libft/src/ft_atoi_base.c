/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:05:43 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/06 15:08:08 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inbase(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= ('a' + base - 10)));
}

int			ft_atoi_base(char *str, int base)
{
	int	value;
	int	sign;

	value = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
			|| *str == '\r' || *str == '\v')
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_inbase(*str, base))
	{
		if (*str - 'a' >= 0)
			value = value * base + (*str - 'a' + 10);
		else
			value = value * base + (*str - '0');
		str++;
	}
	return (value * sign);
}
