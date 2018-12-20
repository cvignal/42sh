/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:55:27 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:20:18 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	*ft_realloc(void *src, size_t old_len, size_t new_len)
{
	void	*res;

	if (!(res = ft_memalloc(new_len)))
		return (NULL);
	ft_memcpy(res, src, old_len);
	ft_memdel(&src);
	return (res);
}
