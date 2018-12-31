/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listtotab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 19:07:30 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/31 11:38:52 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_listtotab(t_list *lst, size_t len)
{
	char	**res;
	int		i;
	t_list	*curr;

	if (!(res = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	i = 0;
	curr = lst;
	while (i < (int)len)
	{
		if (!(res[i] = ft_strdup(curr->content)))
			return (NULL);
		i++;
		curr = curr->next;
	}
	res[i] = NULL;
	return (res);
}
