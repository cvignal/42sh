/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 09:58:40 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/16 16:42:03 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_newlength(const char *str, char *old_p, char *new_p)
{
	size_t	cnt;
	char	*cpy;
	size_t	i;

	cnt = 0;
	cpy = (char *)str;
	i = 0;
	while (cpy[i])
	{
		if (ft_strstr(cpy + i, old_p) == cpy + i)
		{
			cnt++;
			i += ft_strlen(old_p) - 1;
		}
		i++;
	}
	return (i + cnt * (ft_strlen(new_p) - ft_strlen(old_p)));
}

char			*ft_replace_all(const char *str, char *old_p, char *new_p
		, int flag)
{
	char	*ret;
	size_t	new_len;
	char	*cpy;
	size_t	i;

	new_len = ft_newlength(str, old_p, new_p);
	if (!(ret = ft_strnew(new_len)))
		return (NULL);
	cpy = (char *)str;
	i = 0;
	while (*cpy)
	{
		if (ft_strstr(cpy, old_p) == cpy)
		{
			ft_strcpy(ret + i, new_p);
			i += ft_strlen(new_p);
			cpy += ft_strlen(old_p);
		}
		else
			ret[i++] = *cpy++;
	}
	if (flag)
		free((char *)str);
	return (ret);
}
