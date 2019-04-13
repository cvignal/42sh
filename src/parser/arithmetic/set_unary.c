/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 06:30:48 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/13 06:36:41 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"

void	set_unary(t_token *list)
{
	int		prev_is_valid_operand;

	prev_is_valid_operand = 0;
	while (list)
	{
		if (!prev_is_valid_operand)
		{
			if (list->type == TT_ARI_OP_SUB)
				list->type = TT_ARI_OP_USUB;
			else if (list->type == TT_ARI_OP_PLUS)
				list->type = TT_ARI_OP_UPLUS;
		}
		if (list->type == TT_ARI_ID || list->type == TT_ARI_NUMBER
				|| list->type == TT_CLOSE_PAR)
			prev_is_valid_operand = 1;
		else
			prev_is_valid_operand = 0;
		list = list->next;
	}
}
