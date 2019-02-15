/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 15:20:51 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/15 19:32:23 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"

static int		get_hash_index(const char *s)
{
	int	index;

	index = 0;
	if (*s)
	{
		index += *s;
		index <<= 8;
		if (*(s + 1))
			index += *(s + 1);
	}
	return (index);
}

static t_hbt	*alloc_hbt_node(t_shell *shell, const char *bin)
{
	t_hbt		*node;
	char		*path;

	path = find_command(shell, bin);
	if (!path)
		return (NULL);
	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	if (!(node->bin = ft_strdup(bin)))
	{
		free(node);
		return (NULL);
	}
	node->path = path;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void			free_hbt(t_hbt *hbt)
{
	if (hbt)
	{
		free_hbt(hbt->left);
		free_hbt(hbt->right);
		free(hbt->path);
		free(hbt->bin);
		free(hbt);
	}
}

char			*get_hbt_elem(t_shell *shell, t_hbt **hbt, const char *elem)
{
	int		res;

	if (*hbt)
	{
		res = ft_strcmp((*hbt)->bin, elem);
		if (!res)
			return ((*hbt)->path);
		else if (res > 0)
			return (get_hbt_elem(shell, &(*hbt)->left, elem));
		else
			return (get_hbt_elem(shell, &(*hbt)->right, elem));
	}
	else
	{
		if (!(*hbt = alloc_hbt_node(shell, elem)))
			return (NULL);
		return ((*hbt)->path);
	}
}

char			*hbt_command(t_shell *shell, const char *elem)
{
	return (get_hbt_elem(shell, shell->hash_table + get_hash_index(elem),
					elem));
}
