/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfold.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:37:43 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/21 10:30:51 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_del(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

void		*ft_lstfold(t_list *lst, void *(*f)(void *, void *))
{
	t_list *temp;

	temp = lst;
	while (lst->next)
	{
		(lst->next)->content = f(lst->content, lst->next->content);
		temp = lst->next;
		ft_lstdelone(&lst, &ft_del);
		lst = temp;
	}
	return (lst->content);
}
