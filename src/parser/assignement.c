/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:31:34 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 05:36:13 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int	token_is_assignement(const char *value)
{
	int	i;
	int	found_eq;

	if (!ft_isalpha(value[0]) && value[0] != '_')
		return (0);
	i = 1;
	found_eq = 0;
	while (value[i])
	{
		if (!ft_isalnum(value[i]) && value[i] != '_')
		{
			if (value[i] == '=')
				found_eq = 1;
			else
				return (0);
		}
		++i;
	}
	return (found_eq);
}
