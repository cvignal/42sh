/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfindchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 04:49:02 by fstadelw          #+#    #+#             */
/*   Updated: 2018/12/19 16:14:53 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

ssize_t		ft_strfindchar(const char *str, char c)
{
	ssize_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
