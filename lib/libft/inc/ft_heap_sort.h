/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap_sort.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:00:03 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/11 20:41:41 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEAP_SORT_H
# define FT_HEAP_SORT_H

typedef struct		s_heap_sort
{
	int				(*cmp)(void *, void *);
	void			*data;
	size_t			content_size;
	size_t			len;
}					t_heap_sort;

#endif
