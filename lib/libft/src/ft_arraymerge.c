/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraymerge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 00:10:43 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/13 14:13:59 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static int	realloc_array(t_array *table, size_t size)
{
	char	**new_table;
	int		i;

	if (!(new_table = (char **)malloc(size)))
		return (1);
	ft_bzero(new_table, size);
	i = 0;
	while (i < table->length)
	{
		new_table[i] = table->data[i];
		i++;
	}
	if (table->data)
		free(table->data);
	table->data = new_table;
	table->alloc_size = size / sizeof(*table->data);
	return (0);
}

int			ft_arraymerge(t_array *table, t_array *other)
{
	int	i;

	if (table->length + other->length + 2 > table->alloc_size)
	{
		if (realloc_array(table, sizeof(*table->data)
					* (table->length + other->length + 2)))
			return (1);
	}
	i = 0;
	while (i < other->length)
		table->data[table->length++] = other->data[i++];
	return (0);
}
