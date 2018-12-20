/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:04:58 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:21:01 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

char	*ft_strjoin_free(char *s1, char *s2, int flag)
{
	char *res;

	if (!(res = ft_strjoin(s1, s2)))
		return (NULL);
	if (flag == 3)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
		return (res);
	}
	else if (flag == 2)
	{
		ft_strdel(&s2);
		return (res);
	}
	else if (flag == 1)
	{
		ft_strdel(&s1);
		return (res);
	}
	else
		return (res);
}
