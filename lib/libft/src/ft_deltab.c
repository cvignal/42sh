/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deltab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:03:41 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:20:45 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_deltab(char ***table)
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
}
