/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 01:27:36 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/17 02:05:41 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_sort.h"

static inline void	*addr(t_sort *sort, unsigned int n)
{
	return (sort->data + n * sort->content_size);
}

int				partition(t_sort *sort, int first, int last, int pivot)
{
	int	i;
	int	j;

	ft_vswap(addr(sort, pivot), addr(sort, last), sort->content_size);
	j = first;
	i = first;
	while (i <= last - 1)
	{
		if (sort->cmp(addr(sort, i), addr(sort, last)) <= 0)
		{
			ft_vswap(addr(sort, i), addr(sort, j), sort->content_size);
			++j;
		}
		++i;
	}
	ft_vswap(addr(sort, last), addr(sort, j), sort->content_size);
	return (j);
}

void			ft_quicksort_internal(t_sort *sort, int first, int last)
{
	unsigned int	pivot;

	if (first < last)
	{
		pivot = last;
		pivot = partition(sort, first, last, pivot);
		ft_quicksort_internal(sort, first, pivot - 1);
		ft_quicksort_internal(sort, pivot, last);
	}
}

void			ft_quicksort(void *data, size_t content_size, size_t len,
		int	(*cmp)(void *, void *))
{
	t_sort	sort;

	sort.cmp = cmp;
	sort.data = data;
	sort.content_size = content_size;
	sort.len = len;
	if (len)
		ft_quicksort_internal(&sort, 0, (int)len - 1);
}
