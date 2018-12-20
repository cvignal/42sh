/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:05:42 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:18:51 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *cur_elt;

	cur_elt = *alst;
	while (*alst)
	{
		*alst = (*alst)->next;
		ft_lstdelone(&cur_elt, del);
		cur_elt = *alst;
	}
	*alst = NULL;
}
