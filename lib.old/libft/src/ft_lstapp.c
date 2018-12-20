/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstapp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:28:27 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/07 13:28:29 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstapp(t_list **alst, t_list *new)
{
	t_list *elt_cur;

	if (!(*alst))
		*alst = new;
	else if (!new)
		return ;
	else
	{
		elt_cur = *alst;
		while (elt_cur->next)
			elt_cur = elt_cur->next;
		elt_cur->next = new;
	}
}
