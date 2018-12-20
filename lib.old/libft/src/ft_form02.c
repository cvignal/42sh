/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_form02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 12:35:36 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:58:06 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_fill_uns(char *str, t_form *flag)
{
	int	len_w;

	len_w = (int)ft_strlen(str);
	flag->length = ft_max(len_w, flag->width, flag->prec) + 1;
	flag->length += flag->sharp ? (flag->c == 'o') * 1 +
		(flag->c == 'x' || flag->c == 'X') * 2 : 0;
	if (flag->prec < len_w)
		flag->space_nbr = flag->width - len_w +
			(flag->prec == 0 && *str == '0');
	else
		flag->space_nbr = flag->width - flag->prec;
	flag->zero_nbr = (flag->prec > len_w ? flag->prec - len_w : 0);
	flag->space_nbr -= flag->sharp ? (flag->c == 'o') * 1
		+ (flag->c == 'x' || flag->c == 'X') * 2 : 0;
	if (flag->zero && !flag->minus)
	{
		flag->zero_nbr += flag->space_nbr;
		flag->space_nbr = 0;
	}
}

char	*ft_form_uns(char *str, t_form flag)
{
	char	*ret;
	int		i;

	ft_fill_uns(str, &flag);
	if (flag.minus)
		return (ft_form_minusu(str, flag));
	if (!(ret = ft_strnew(flag.length)))
		return (NULL);
	i = 0;
	while (flag.space_nbr-- > 0)
		ret[i++] = ' ';
	if (flag.sharp && flag.zero_nbr <= 0 && flag.c == 'o')
		(*str != '0' || !flag.prec) ? ret[i++] = '0' : 0;
	if (flag.sharp && (flag.c == 'x' || flag.c == 'X') && *str != '0')
	{
		ret[i++] = '0';
		ret[i++] = flag.c;
	}
	while (flag.zero_nbr-- > 0)
		ret[i++] = '0';
	if (!(flag.prec == 0 && *str == '0'))
		ft_strcpy(ret + i, str);
	ret[ft_strlen(ret)] = '0';
	ft_strdel(&str);
	return (ret);
}

char	*ft_form_minusu(char *str, t_form flag)
{
	char	*ret;
	int		i;

	if (!(ret = ft_strnew(flag.length)))
		return (NULL);
	i = 0;
	flag.sharp ? ret[i++] = '0' : 0;
	flag.sharp && (flag.c == 'x' || flag.c == 'X') ? ret[i++] = 'x' : 0;
	while (flag.zero_nbr-- > 0)
		ret[i++] = '0';
	ft_strcpy(ret + i, str);
	i = (int)ft_strlen(ret);
	while (flag.space_nbr-- > 0)
		ret[i++] = ' ';
	ret[ft_strlen(ret)] = '0';
	ft_strdel(&str);
	return (ret);
}
