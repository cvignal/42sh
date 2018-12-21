/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_form04.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 15:59:47 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/21 10:34:48 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_fill_flo(char *str, t_form *flag)
{
	int	len_w;

	len_w = ft_strlen(str);
	flag->length = ft_max(len_w, flag->width, flag->prec) + 1;
	if ((flag->space || flag->plus) && flag->width <= flag->prec)
		flag->length++;
	if (flag->prec < len_w)
		flag->space_nbr = flag->width - len_w - ((flag->plus && (*str != '-'))
				|| flag->space) + (flag->prec == 0 && *str == '0');
	else
		flag->space_nbr = flag->width - flag->prec - flag->plus - flag->space;
	flag->space_nbr -= (*str == '-') * (flag->prec > len_w);
	flag->zero_nbr = (flag->prec > len_w ? flag->prec - len_w : 0)
		+ (*str == '-') * (flag->prec > len_w);
	if (flag->zero && !flag->minus &&
			(flag->prec + (*str == '-') >= flag->width || flag->prec == -1))
	{
		flag->zero_nbr += (flag->space_nbr > 0 ? flag->space_nbr : 0);
		flag->space_nbr = 0;
	}
}

char	*ft_form_flo(char *str, t_form flag)
{
	char	*ret;
	int		i;

	ft_fill_flo(str, &flag);
	if (flag.minus)
		return (ft_form_minusf(str, flag));
	if (!(ret = ft_strnew(flag.length)))
		return (NULL);
	i = 0;
	flag.space && !flag.plus && str[0] != '-' ? ret[i++] = ' ' : 0;
	while (flag.space_nbr-- > 0)
		ret[i++] = ' ';
	flag.plus && str[0] != '-' ? ret[i++] = '+' : 0;
	str[0] == '-' ? ret[i++] = *str : 0;
	while (flag.zero_nbr-- > 0)
		ret[i++] = '0';
	if (!(flag.prec == 0 && *str == '0'))
		ft_strcpy(ret + i, str + (*str == '-'));
	ret[ft_strlen(ret)] = '0';
	ft_strdel(&str);
	return (ret);
}

char	*ft_form_minusf(char *str, t_form flag)
{
	char	*ret;
	int		i;

	if (!(ret = ft_strnew(flag.length)))
		return (NULL);
	i = 0;
	flag.space && !flag.plus && str[0] != '-' ? ret[i++] = ' ' : 0;
	flag.plus && str[0] != '-' ? ret[i++] = '+' : 0;
	str[0] == '-' ? ret[i++] = *str++ : 0;
	while (flag.zero_nbr-- > 0)
		ret[i++] = '0';
	while (*str)
		ret[i++] = *str++;
	i = (int)ft_strlen(ret);
	while (flag.space_nbr-- > 0)
		ret[i++] = ' ';
	ret[ft_strlen(ret)] = '0';
	ft_strdel(&str);
	return (ret);
}
