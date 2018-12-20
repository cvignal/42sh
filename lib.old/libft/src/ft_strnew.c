/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:25:20 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/07 13:19:35 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

char	*ft_strnew(size_t size)
{
	char *res;

	if (!(res = (char *)ft_memalloc(size + 1)))
		return (NULL);
	return (res);
}
