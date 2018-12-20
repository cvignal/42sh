/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 12:01:30 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:59:25 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

char	*ft_insert_free(char *str, char *to_insert, size_t index, int flag)
{
	char	*ret;

	if (!(ret = ft_strnew(ft_strlen(str) + ft_strlen(to_insert))))
		return (NULL);
	ft_strncpy(ret, str, index);
	ft_strcat(ret, to_insert);
	ft_strcat(ret, str + index);
	if (flag == 1)
		ft_strdel(&str);
	else if (flag == 2)
		ft_strdel(&to_insert);
	else if (flag == 3)
	{
		ft_strdel(&str);
		ft_strdel(&to_insert);
	}
	return (ret);
}
