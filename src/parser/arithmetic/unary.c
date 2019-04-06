/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unary.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 03:28:50 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/06 03:38:15 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"

void	set_unary_operator(t_token *token)
{
	int	is_prev_id;

	while (token && token->type != TT_ARI_BEGIN)
		token = token->next;
	is_prev_id = 0;
	while (token && token->type != TT_ARI_END)
	{
		if (token->type == TT_ARI_OP_PLUS && is_prev_id)
			token->type = TT_ARI_OP_UPLUS;
		else if (token->type == TT_ARI_OP_SUB && is_prev_id)
			token->type = TT_ARI_OP_USUB;
		if (token->type == TT_ARI_ID || token->type == TT_CLOSE_PAR)
			is_prev_id = 1;
		else
			is_prev_id = 0;
		token = token->next;
	}
}
