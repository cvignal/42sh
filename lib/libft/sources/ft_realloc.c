/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:35:53 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/12 09:01:07 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

void		*ft_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	size_t	i;
	void	*new_ptr;

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (i < old_size && i < new_size)
	{
		((unsigned char *)new_ptr)[i] = ((unsigned char *)old_ptr)[i];
		++i;
	}
	while (i < new_size)
	{
		((unsigned char *)new_ptr)[i] = 0;
		++i;
	}
	if (old_size)
		free(old_ptr);
	return (new_ptr);
}
