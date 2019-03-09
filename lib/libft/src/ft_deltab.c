/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deltab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:03:41 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/09 15:02:48 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_deltab(char ***table)
{
	int	i;

	i = 0;
	while ((*table)[i])
	{
		ft_strdel(&((*table)[i]));
		i++;
	}
	free(*table);
	*table = NULL;
	return (NULL);
}
