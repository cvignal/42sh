/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:30:23 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/24 17:30:34 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SORT_H
# define FT_SORT_H

typedef struct		s_sort
{
	int				(*cmp)(void *, void *);
	void			*data;
	size_t			content_size;
	size_t			len;
}					t_sort;

#endif
