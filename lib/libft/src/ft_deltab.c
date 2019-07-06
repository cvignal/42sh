/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deltab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:03:41 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/06 16:23:01 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_deltab(char ***table)
{
	int	i;

	i = 0;
	while (*table != NULL && (*table)[i])
	{
		ft_strdel(&((*table)[i]));
		i++;
	}
	free(*table);
	*table = NULL;
	return (NULL);
}
