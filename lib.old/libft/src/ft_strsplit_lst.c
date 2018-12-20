/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:32:01 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:19:30 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static size_t	ft_lenword(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

t_list			*ft_strsplit_lst(char const *s, char c)
{
	t_list			*words_list;
	t_list			*new_elem;

	words_list = NULL;
	new_elem = NULL;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!(new_elem = ft_lstnew(ft_strsub(s, 0,
						ft_lenword(s, c)), ft_lenword(s, c) + 1)))
				return (NULL);
			ft_lstapp(&words_list, new_elem);
		}
		s += ft_lenword(s, c);
	}
	return (words_list);
}
