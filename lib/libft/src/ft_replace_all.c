/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 09:58:40 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/20 11:09:24 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_newlength(const char *str, char *old_p, char *new_p)
{
	size_t	ret;
	size_t	diff;
	char	*cpy;

	ret = ft_strlen(str);
	diff = ft_strlen(new_p) - ft_strlen(old_p);
	cpy = (char *)str;
	while (ft_strstr(cpy, old_p))
	{
		ret += diff;
		if (ft_strlen(cpy) > ft_strlen(ft_strstr(cpy, old_p)))
			cpy = ft_strstr(cpy, old_p) + 1;
		else
			break ;
	}
	return (ret);
}

char			*ft_replace_all(const char *str, char *old_p, char *new_p
		, int flag)
{
	char	*ret;
	size_t	new_len;
	char	*cpy;

	new_len = ft_newlength(str, old_p, new_p);
	if (!(ret = ft_strnew(new_len)))
		return (NULL);
	cpy = (char *)str;
	while (ft_strstr(cpy, old_p))
	{
		new_len = ft_strlen(cpy) - ft_strlen(ft_strstr(cpy, old_p));
		ft_strncat(ret, cpy, new_len);
		ft_strcat(ret, new_p);
		cpy = ft_strstr(cpy, old_p) + ft_strlen(old_p);
	}
	if (!ft_strequ(cpy, old_p))
		ft_strcat(ret, cpy);
	if (flag)
		free((char *)str);
	return (ret);
}
