/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:31:34 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/11 08:33:53 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int	token_is_assignement(const char *value)
{
	int	i;

	if (!ft_isalpha(value[0]) && value[0] != '_')
		return (0);
	i = 1;
	while (value[i] && value[i] != '=')
	{
		if (!ft_isalnum(value[i]) && value[i] != '_')
			return (0);
		if (i > VAR_MAX)
			return (0);
		++i;
	}
	return (value[i] == '=');
}
