/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 22:23:03 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/03 11:29:49 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_buf_str(char **str, char *buffer)
{
	int			res;
	static int	i = 0;

	res = (int)ft_strlen(*str) - 1;
	ft_strncpy(buffer + i, *str, res);
	i += res;
	return (res);
}

int		ft_sprintf(char *buffer, const char *str, ...)
{
	va_list	ap;
	char	*buf;
	int		res;

	va_start(ap, str);
	res = 0;
	while (*str)
	{
		if (*str == '%' && ft_valid_percent(&str))
		{
			if (!ft_readpercent(&buf, &str, ap))
				return (0);
			res += ft_buf_str(&buf, buffer);
		}
		else
		{
			if (!ft_readstr(&buf, &str))
				return (0);
			res += ft_buf_str(&buf, buffer);
		}
	}
	va_end(ap);
	return (res);
}
