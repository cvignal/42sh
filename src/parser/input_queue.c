/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:22:45 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/16 19:14:31 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"

void	free_input_queue(t_ast_token *input)
{
	t_ast_token	*tmp;

	while (input)
	{
		if (input->type == TT_CMD)
			((t_ast *)input->data)->del(input->data);
		else
			free(input->data);
		tmp = input;
		input = input->next;
		free(tmp);
	}
}
