/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_form01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 12:16:34 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:57:54 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_fill_str(char *str, t_form *flag)
{
	int	len_w;

	len_w = (int)ft_strlen(str);
	if (!flag->prec && flag->c == 's')
		len_w = 0;
	flag->length = ft_max(len_w, flag->width, 0) + 1;
	if (flag->prec > len_w)
		flag->space_nbr = flag->width - len_w;
	else
		flag->space_nbr = flag->width - (flag->prec <= 0 ? len_w : flag->prec);
	flag->zero_nbr = 0;
	flag->space_nbr -= ((flag->c == 'c' || flag->c == '%') && !*str);
	flag->space_nbr += (flag->c == 's' && !flag->prec && len_w);
	if (flag->zero && !flag->minus)
	{
		flag->zero_nbr += flag->space_nbr;
		flag->space_nbr = 0;
	}
	flag->prec == -1 ? flag->prec = len_w : 0;
}

char	*ft_form_str(char *str, t_form flag)
{
	int		i;
	char	*ret;

	ft_fill_str(str, &flag);
	if (flag.minus)
		return (ft_form_minuss(str, flag));
	if (!(ret = ft_strnew(flag.length)))
		return (NULL);
	i = 0;
	while (flag.space_nbr-- > 0)
		ret[i++] = ' ';
	while (flag.zero_nbr-- > 0)
		ret[i++] = '0';
	if (flag.c == 's')
		ft_strncpy(ret + i, str, flag.prec);
	else
		ret[i] = *str;
	if (flag.c == 'c' && !*str)
		ret[ft_strlen(ret)] = '1';
	else
		ret[ft_strlen(ret)] = '0';
	ft_strdel(&str);
	return (ret);
}

char	*ft_form_minuss(char *str, t_form flag)
{
	char	*ret;
	int		i;

	if (!(ret = ft_strnew(flag.length)))
		return (NULL);
	ft_strncpy(ret, str, flag.prec);
	i = (int)ft_strlen(ret);
	while (flag.space_nbr-- > 0)
		ret[i++] = ' ';
	if (flag.c == 'c' && !*str)
		ret[ft_strlen(ret)] = '1';
	else
		ret[ft_strlen(ret)] = '0';
	ft_strdel(&str);
	return (ret);
}
