/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:14:35 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/08 21:36:07 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "expand.h"
#include "libft.h"

static int	realloc_exp_buff(t_exp_buff *buffer)
{
	char			*new_buffer;
	unsigned int	i;

	new_buffer = malloc(sizeof(*new_buffer) * (EXP_BUFFER_ALLOC_SIZE
			+ buffer->alloc_size + 1));
	if (!new_buffer)
		return (1);
	i = 0;
	while (i < buffer->pos)
	{
		new_buffer[i] = buffer->buffer[i];
		++i;
	}
	ft_bzero(new_buffer + buffer->alloc_size, EXP_BUFFER_ALLOC_SIZE);
	free(buffer->buffer);
	buffer->buffer = new_buffer;
	buffer->alloc_size += EXP_BUFFER_ALLOC_SIZE;
	return (0);
}

int			add_to_exp_buff(t_exp_buff *buffer, char c)
{
	if (buffer->pos + 1 >= buffer->alloc_size)
	{
		if (realloc_exp_buff(buffer))
			return (1);
	}
	buffer->buffer[buffer->pos++] = c;
	return (0);
}
