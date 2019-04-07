/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:47:27 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/07 01:48:32 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"

void	free_ari(t_ast *ast)
{
	if (ast)
	{
		if (ast->data)
			free(ast->data);
		free_ari(ast->left);
		free_ari(ast->right);
		free(ast);
	}
}
