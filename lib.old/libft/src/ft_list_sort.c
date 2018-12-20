/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:20:00 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:20:31 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static t_list	*ft_merge_and_sort(t_list *list1, t_list *list2, int (*cmp)())
{
	t_list *result;

	if (!list1)
		return (list2);
	else if (!list2)
		return (list1);
	if (cmp(list1->content, list2->content) <= 0)
	{
		result = list1;
		result->next = ft_merge_and_sort(list1->next, list2, cmp);
	}
	else
	{
		result = list2;
		result->next = ft_merge_and_sort(list1, list2->next, cmp);
	}
	return (result);
}

static void		ft_split_list(t_list *head, t_list **list1, t_list **list2)
{
	t_list *slow;
	t_list *fast;

	slow = head;
	fast = head->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*list1 = head;
	*list2 = slow->next;
	slow->next = NULL;
}

void			ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list *head;
	t_list *tmp1;
	t_list *tmp2;

	head = *begin_list;
	if (!head || !head->next)
		return ;
	ft_split_list(head, &tmp1, &tmp2);
	ft_list_sort(&tmp1, cmp);
	ft_list_sort(&tmp2, cmp);
	*begin_list = ft_merge_and_sort(tmp1, tmp2, cmp);
}
