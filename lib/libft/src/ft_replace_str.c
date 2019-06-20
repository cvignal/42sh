/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 11:57:24 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/13 14:08:42 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_replace_str(char *dst, char *src, char *old_p, char *new_p)
{
	size_t	len_first;
	size_t	i;

	if (!ft_strlen(old_p) && ft_strlen(new_p))
	{
		i = 0;
		while (src[i])
		{
			ft_strcat(dst, new_p);
			i++;
		}
		return ;
	}
	if (!ft_strstr(src, old_p))
	{
		ft_strcpy(dst, src);
		return ;
	}
	len_first = ft_strlen(src) - ft_strlen(ft_strstr(src, old_p));
	ft_strncpy(dst, src, len_first);
	ft_strcat(dst, new_p);
	ft_strcat(dst, src + len_first + ft_strlen(old_p));
}
