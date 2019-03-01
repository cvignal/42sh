/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 14:30:42 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/01 15:14:52 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void	print_rec_tree(t_hbt *node)
{
	if (node)
	{
		if (node->path)
			ft_printf("%s\n", node->path);
		print_rec_tree(node->left);
		print_rec_tree(node->right);
	}
}
