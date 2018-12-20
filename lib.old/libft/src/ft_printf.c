/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 11:21:07 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/03 11:27:49 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_readpercent(char **line, const char **str, va_list ap)
{
	int		size;
	char	*tmp;

	size = 1;
	while (!ft_is_conv((*str)[size]))
		size++;
	if (!(tmp = ft_strnew(size)))
		return (0);
	ft_strncpy(tmp, *str + 1, size);
	if (!(*line = ft_conv(tmp, ap)))
		return (0);
	*str += size + 1;
	ft_strdel(&tmp);
	return (1);
}

int		ft_readstr(char **line, const char **str)
{
	int	size;

	size = 0;
	while ((*str)[size] != '%' && (*str)[size])
		size++;
	if (!(*line = ft_strnew(size)))
		return (0);
	ft_strncpy(*line, *str, size);
	*str += size;
	return (1);
}

int		ft_valid_percent(const char **s)
{
	int i;

	i = 1;
	while ((*s)[i] == ' ' || (*s)[i] == '.' || ((*s)[i] >= '0'
				&& (*s)[i] <= '9') || (*s)[i] == '#'
			|| (*s)[i] == 'l' || (*s)[i] == 'h' || (*s)[i] == '+'
			|| (*s)[i] == '-' || (*s)[i] == 'L' || (*s)[i] == 'j'
			|| (*s)[i] == 'z' || (*s)[i] == '*')
		i++;
	if (!ft_is_conv((*s)[i]))
	{
		*s += i;
		return (0);
	}
	return (1);
}

int		ft_printf(const char *str, ...)
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
			res += ft_print_conv(&buf);
		}
		else
		{
			if (!ft_readstr(&buf, &str))
				return (0);
			res += ft_print_str(&buf);
		}
	}
	va_end(ap);
	return (res);
}

int		ft_dprintf(int fd, const char *str, ...)
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
			res += ft_print_convfd(&buf, fd);
		}
		else
		{
			if (!ft_readstr(&buf, &str))
				return (0);
			res += ft_print_strfd(&buf, fd);
		}
	}
	va_end(ap);
	return (res);
}
