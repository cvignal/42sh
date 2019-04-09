/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:37:53 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/09 04:14:08 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

int	exec_ari_plus(t_shell *shell, t_ast *ast)
{
	int	a;
	int	b;
	int	res;

	(void)shell;
	if (!ast->left->data || !ast->right->data)
		return (1);
	a = ft_atoi(ast->left->data);
	b = ft_atoi(ast->right->data);
	free(ast->data);
	res = a + b;
	ast->data = ft_itoa(res);
	ast->ret = !res;
	return (res);
}
