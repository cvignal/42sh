/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayadd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:32:22 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/13 10:08:42 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static int	realloc_array(t_array *table)
{
	char	**new_table;
	int		i;
	int		size;

	size = sizeof(char *) * (table->alloc_size + ARRAY_ALLOC_SIZE);
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
	table->alloc_size += ARRAY_ALLOC_SIZE;
	return (0);
}

int			ft_arrayadd(t_array *table, char *str)
{
	if (table->length + 2 > table->alloc_size)
	{
		if (realloc_array(table))
			return (1);
	}
	if (!(table->data[table->length] = ft_strdup(str)))
		return (1);
	table->length++;
	return (0);
}
