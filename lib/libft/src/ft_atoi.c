/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 12:59:53 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/08 10:24:14 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_atoi(const char *str)
{
	int res;
	int is_neg;

	res = 0;
	is_neg = 0;
	while (*str == '\t' || *str == ' ' || *str == '\n' ||
			*str == '\v' || *str == '\f' || *str == '\r' || *str == '0')
		str++;
	if (*str == '+' || *str == '-')
	{
		is_neg = (*str == '-' ? 1 : 0);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (is_neg ? -res : res);
}
