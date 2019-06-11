/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:41:09 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/11 17:00:19 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_heap_sort.h"

static inline void	*addr(t_heap_sort *hs, unsigned int n)
{
	return ((unsigned char *)hs->data + n * hs->content_size);
}

static void	heapify(t_heap_sort *hs, unsigned int node, unsigned int n)
{
	unsigned int	i;

	i = node << 1;
	while (i <= n)
	{
		if (i < n && hs->cmp(addr(hs, i), addr(hs, i + 1)) < 0)
			++i;
		if (hs->cmp(addr(hs, node), addr(hs, i)) < 0)
		{
			ft_vswap(addr(hs, node), addr(hs, i), hs->content_size);
			node = i;
			i <<= 1;
		}
		else
			++i;
	}
}

void		ft_heap_sort(void *data, size_t content_size, size_t len,
		int (*cmp)(void *, void *))
{
	t_heap_sort		hs;
	int				i;

	hs.data = data;
	hs.content_size = content_size;
	hs.len = len;
	hs.cmp = cmp;
	i = (len >> 1) + 1;
	while (i-- > 0)
		heapify(&hs, i, len - 1);
	i = len - 1;
	while (i > 0)
	{
		ft_vswap(addr(&hs, 0), addr(&hs, i), hs.content_size);
		heapify(&hs, 0, i - 1);
		--i;
	}
}
