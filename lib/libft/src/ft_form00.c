/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_form00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:00:56 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:57:42 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_fill_ptr(char *str, t_form *flag)
{
	int	len_w;

	len_w = (int)ft_strlen(str);
	flag->length = ft_max(len_w, flag->width, flag->prec) + 3;
	if (flag->prec < len_w)
		flag->space_nbr = flag->width - len_w;
	else
		flag->space_nbr = (flag->width == -1 ? 0 : flag->width) - flag->prec;
	flag->zero_nbr = (flag->prec > len_w ? flag->prec - len_w : 0);
	flag->space_nbr -= 2;
	if (flag->zero)
	{
		flag->zero_nbr += flag->space_nbr;
		flag->space_nbr = 0;
	}
}

char	*ft_form_minusp(char *str, t_form flag)
{
	char	*ret;
	int		i;

	if (!(ret = ft_strnew(flag.length)))
		return (NULL);
	i = 0;
	ret[i++] = '0';
	ret[i++] = 'x';
	while (flag.zero_nbr-- > 0)
		ret[i++] = '0';
	if (flag.c != 'p' || *str != '0' || flag.width > 0 || flag.prec == -1)
		ft_strcpy(ret + i, str);
	i = (int)ft_strlen(ret);
	while (flag.space_nbr-- > 0)
		ret[i++] = ' ';
	ret[ft_strlen(ret)] = '0';
	ft_strdel(&str);
	return (ret);
}

char	*ft_form_ptr(char *str, t_form flag)
{
	char	*ret;
	int		i;

	ft_fill_ptr(str, &flag);
	if (flag.minus)
		return (ft_form_minusp(str, flag));
	if (!(ret = ft_strnew(flag.length)))
		return (NULL);
	i = 0;
	while (flag.space_nbr-- > 0)
		ret[i++] = ' ';
	ret[i++] = '0';
	ret[i++] = 'x';
	while (flag.zero_nbr-- > 0)
		ret[i++] = '0';
	if (flag.c != 'p' || *str != '0' || flag.width > 0 || flag.prec)
		ft_strcpy(ret + i, str);
	ret[ft_strlen(ret)] = '0';
	ft_strdel(&str);
	return (ret);
}
