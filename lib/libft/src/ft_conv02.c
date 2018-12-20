/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 12:02:11 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:57:25 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <stdlib.h>

char	*ft_conv_str(va_list ap, t_form flag)
{
	char *str;

	str = va_arg(ap, char *);
	flag.size[0] = flag.c;
	if (!str)
		return (ft_strdup("(null)"));
	if (!*str)
		return (ft_strdup(""));
	return (ft_strdup(str));
}

char	*ft_conv_int(va_list ap, t_form flag)
{
	long long	c;
	char		*str;

	if (ft_strequ(flag.size, "l"))
		c = va_arg(ap, long);
	else if (ft_strequ(flag.size, "ll"))
		c = va_arg(ap, long long);
	else if (ft_strequ(flag.size, "h"))
		c = (short)va_arg(ap, int);
	else if (ft_strequ(flag.size, "hh"))
		c = (char)va_arg(ap, int);
	else if (ft_strequ("j", flag.size))
		c = (intmax_t)va_arg(ap, intmax_t);
	else if (ft_strequ("z", flag.size))
		c = (size_t)va_arg(ap, size_t);
	else
		c = va_arg(ap, int);
	str = ft_ltoa_base(c, 10);
	return (str);
}

char	*ft_conv_percent(va_list ap, t_form flag)
{
	va_list res;

	flag.size[0] = flag.c;
	va_copy(res, ap);
	return (ft_strdup(&flag.c));
}

char	*ft_conv_uns(va_list ap, t_form flag)
{
	unsigned long long	c;
	char				*str;

	if (ft_strequ(flag.size, "l"))
		c = va_arg(ap, unsigned long);
	else if (ft_strequ(flag.size, "ll"))
		c = va_arg(ap, unsigned long long);
	else if (ft_strequ(flag.size, "h"))
		c = (unsigned short)va_arg(ap, unsigned int);
	else if (ft_strequ(flag.size, "hh"))
		c = (unsigned char)va_arg(ap, unsigned int);
	else if (ft_strequ("j", flag.size))
		c = (intmax_t)va_arg(ap, intmax_t);
	else if (ft_strequ("z", flag.size))
		c = (size_t)va_arg(ap, size_t);
	else
		c = va_arg(ap, unsigned int);
	str = ft_ultoa_base(c, 10);
	return (str);
}

char	*ft_conv_binary(va_list ap, t_form flag)
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
	str = ft_ltoa_base(i, 2);
	return (str);
}
