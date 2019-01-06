/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 08:49:50 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 09:20:05 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"

void	shift_ast_token(t_ast_token *list, int del)
{
	t_ast_token	*tmp;

	if (del == 1)
		free(list->data);
	else if (del == 2)
		((t_ast *)list->data)->del(list->data);
	if (list->next)
	{
		list->data = list->next->data;
		list->type = list->next->type;
		tmp = list->next->next;
		free(list->next);
		list->next = tmp;
	}
	else
	{
		list->data = NULL;
		list->type = TT_OVER;
		list->next = NULL;
	}
}
