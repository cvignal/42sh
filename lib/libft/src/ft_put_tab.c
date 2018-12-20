/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdrai <gdrai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:55:45 by gdrai             #+#    #+#             */
/*   Updated: 2018/12/19 16:58:47 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int		ft_print_conv(char **str)
{
	int	res;

	res = ft_strlen(*str) - 1;
	write(1, *str, res);
	if ((*str)[res] == '1')
	{
		write(1, "\0", 1);
		res++;
	}
	ft_strdel(str);
	return (res);
}

int		ft_print_str(char **str)
{
	int	res;

	res = ft_strlen(*str);
	write(1, *str, res);
	ft_strdel(str);
	return (res);
}

int		ft_print_convfd(char **str, int fd)
{
	int	res;

	res = ft_strlen(*str) - 1;
	write(fd, *str, res);
	if ((*str)[res] == '1')
	{
		write(fd, "\0", 1);
		res++;
	}
	ft_strdel(str);
	return (res);
}

int		ft_print_strfd(char **str, int fd)
{
	int res;

	res = ft_strlen(*str);
	write(fd, *str, res);
	ft_strdel(str);
	return (res);
}
