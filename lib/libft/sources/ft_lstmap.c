/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:19:15 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/10 09:53:58 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static void		del_list(t_list *list)
{
	if (list)
	{
		del_list(list->next);
		free(list->content);
		free(list);
	}
}

static void		ft_lstaddend_f(t_list **lst, t_list *new_node,
		t_list *(*f)(t_list *))
{
	t_list		*i;

	i = *lst;
	if (i)
	{
		while (i->next)
			i = i->next;
	}
	new_node = f(new_node);
	if (!new_node)
	{
		del_list(*lst);
		*lst = NULL;
	}
	else
	{
		if (!*lst)
			*lst = new_node;
		else
			i->next = new_node;
	}
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *))
{
	t_list	*res;

	res = NULL;
	while (lst)
	{
		ft_lstaddend_f(&res, lst, f);
		lst = lst->next;
	}
	return (res);
}
