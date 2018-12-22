/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 19:07:57 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/22 19:16:42 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap(char **array, int p1, int p2)
{
	char	*tmp;

	tmp = array[p1];
	array[p1] = array[p2];
	array[p2] = tmp;
}

void		quicksort(char **array, int first, int last)
{
	char	*pivot;
	int		i;
	int		j;

	if (last - first > 1)
	{
		pivot = array[last];
		i = first;
		j = first;
		while (i < last)
		{
			if (ft_strcmp(array[i], pivot) < 0)
				ft_swap(array, i, j++);
			++i;
		}
		ft_swap(array, last, j);
		quicksort(array, first, j - 1);
		quicksort(array, j + 1, last);
	}
}
