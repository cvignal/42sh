/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:17:11 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:22:34 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <stdlib.h>

char	*ft_conv_octal(va_list ap, t_form flag)
{
	unsigned long long	i;
	char				*str;

	if (ft_strequ("l", flag.size))
		i = va_arg(ap, unsigned long);
	else if (ft_strequ("ll", flag.size))
		i = va_arg(ap, unsigned long long);
	else if (ft_strequ("h", flag.size))
		i = (unsigned short)va_arg(ap, unsigned int);
	else if (ft_strequ("hh", flag.size))
		i = (unsigned char)va_arg(ap, unsigned int);
	else if (ft_strequ("j", flag.size))
		i = (intmax_t)va_arg(ap, intmax_t);
	else if (ft_strequ("z", flag.size))
		i = (size_t)va_arg(ap, size_t);
	else
		i = va_arg(ap, unsigned int);
	if (!i)
		return (ft_strdup("0"));
	str = ft_ltoa_base(i, 8);
	return (str);
}

char	*ft_conv_hexa(va_list ap, t_form flag)
{
	long long	i;
	char		*str;

	if (ft_strequ("l", flag.size) || flag.c == 'p')
		i = va_arg(ap, unsigned long);
	else if (ft_strequ("ll", flag.size))
		i = va_arg(ap, unsigned long long);
	else if (ft_strequ("h", flag.size))
		i = (unsigned short)va_arg(ap, unsigned int);
	else if (ft_strequ("hh", flag.size))
		i = (unsigned char)va_arg(ap, unsigned int);
	else if (ft_strequ("j", flag.size))
		i = (intmax_t)va_arg(ap, uintmax_t);
	else if (ft_strequ("z", flag.size))
		i = (size_t)va_arg(ap, size_t);
	else
		i = va_arg(ap, unsigned int);
	if (!i)
		return (ft_strdup("0"));
	str = ft_ltoa_base(i, 16);
	return (str);
}

char	*ft_conv_hexam(va_list ap, t_form flag)
{
	long long	i;
	char		*str;

	if (ft_strequ("l", flag.size))
		i = va_arg(ap, unsigned long);
	else if (ft_strequ("ll", flag.size))
		i = va_arg(ap, unsigned long long);
	else if (ft_strequ("h", flag.size))
		i = (unsigned short)va_arg(ap, unsigned int);
	else if (ft_strequ("hh", flag.size))
		i = (unsigned char)va_arg(ap, unsigned int);
	else if (ft_strequ("j", flag.size))
		i = (intmax_t)va_arg(ap, uintmax_t);
	else if (ft_strequ("z", flag.size))
		i = (size_t)va_arg(ap, size_t);
	else
		i = va_arg(ap, unsigned int);
	if (!i)
		return (ft_strdup("0"));
	if (!(str = ft_ltoa_base(i, 16)))
		return (NULL);
	i = -1;
	while (str[++i])
		str[i] > 96 && str[i] < 103 ? str[i] -= 32 : 0;
	return (str);
}

char	*ft_conv_char(va_list ap, t_form flag)
{
	int		c;
	char	*str;

	flag.size[0] = flag.c;
	c = va_arg(ap, int);
	if (!(str = (char *)malloc(sizeof(char) * 2)))
		return (NULL);
	str[0] = (char)c;
	str[1] = '\0';
	return (str);
}

char	*ft_conv_float(va_list ap, t_form flag)
{
	long double	c;
	char		*str;

	if (ft_strequ("l", flag.size))
		c = (double)va_arg(ap, double);
	else if (ft_strequ("L", flag.size))
		c = va_arg(ap, long double);
	else
		c = (double)va_arg(ap, double);
	str = ft_dtoa(c, flag.prec);
	return (str);
}
