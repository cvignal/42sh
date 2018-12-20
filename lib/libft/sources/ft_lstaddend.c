/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 09:47:50 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/10 09:49:46 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **list, t_list *new_node)
{
	t_list	*i;

	if (!*list)
		*list = new_node;
	else
	{
		i = *list;
		while (i->next)
			i = i->next;
		i->next = new_node;
	}
}
