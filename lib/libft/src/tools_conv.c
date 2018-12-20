/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 12:04:30 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 21:26:07 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_conv		g_conv[] =
{
	{'c', &ft_conv_char},
	{'s', &ft_conv_str},
	{'p', &ft_conv_hexa},
	{'d', &ft_conv_int},
	{'i', &ft_conv_int},
	{'%', &ft_conv_percent},
	{'o', &ft_conv_octal},
	{'x', &ft_conv_hexa},
	{'X', &ft_conv_hexam},
	{'u', &ft_conv_uns},
	{'f', &ft_conv_float},
	{'b', &ft_conv_binary}
};

t_format	g_format[] =
{
	{'c', &ft_form_str},
	{'s', &ft_form_str},
	{'p', &ft_form_ptr},
	{'d', &ft_form_int},
	{'i', &ft_form_int},
	{'%', &ft_form_str},
	{'o', &ft_form_uns},
	{'x', &ft_form_uns},
	{'X', &ft_form_uns},
	{'u', &ft_form_uns},
	{'f', &ft_form_flo},
	{'b', &ft_form_uns}
};

int		ft_is_conv(char c)
{
	return (c == 'c' || c == 's' || c == 'd' || c == 'i' || c == 'f'
			|| c == 'o' || c == 'X' || c == 'x' || c == 'u' || c == 'p'
			|| c == '%' || c == 'b');
}

void	ft_wildcard(char *tmp, t_form *new, va_list ap)
{
	if (*tmp == '.')
	{
		new->prec = va_arg(ap, int);
		if (new->prec < 0)
			new->prec = -1;
	}
	else
	{
		new->width = va_arg(ap, int);
		if (new->width < 0)
		{
			new->minus = 1;
			new->width *= -1;
		}
	}
}

void	ft_type_percent(char *tmp, t_form *new, va_list ap)
{
	while (!ft_is_conv(*tmp))
	{
		*tmp == '-' ? new->minus = 1 : 0;
		*tmp == '+' ? new->plus = 1 : 0;
		*tmp == ' ' ? new->space = 1 : 0;
		*tmp == '#' ? new->sharp = 1 : 0;
		*tmp == '*' ? new->width = va_arg(ap, int) : 0;
		if (*tmp == '0' && new->width == -1 && new->prec == -1)
			new->zero = 1;
		else if (*tmp >= '0' && *tmp <= '9' && new->prec == -1)
		{
			new->width = ft_atoi(tmp);
			tmp += ft_nb_digits(new->width, 10) - 1;
		}
		else if (*tmp == '.')
		{
			new->prec = ft_atoi(tmp + 1);
			tmp += ft_nb_digits(new->prec, 10) - 1;
		}
		if (*tmp == 'l' || *tmp == 'h' || *tmp == 'L'
				|| *tmp == 'j' || *tmp == 'z')
			ft_strncpy(new->size, tmp, *(tmp + 1) == *tmp ? 2 : 1);
		tmp++;
	}
	new->c = *tmp;
}

void	initialize(t_form *new)
{
	new->width = -1;
	new->prec = -1;
	new->plus = 0;
	new->minus = 0;
	new->sharp = 0;
	new->space = 0;
	new->zero = 0;
	new->c = 0;
	ft_strcpy(new->size, "\0\0\0");
}

char	*ft_conv(char *tmp, va_list ap)
{
	int		i;
	t_form	to_treat;

	initialize(&to_treat);
	ft_type_percent(tmp, &to_treat, ap);
	i = 0;
	while (g_conv[i].conv != to_treat.c)
		i++;
	return (g_format[i].f_form(g_conv[i].f_conv(ap, to_treat), to_treat));
}
