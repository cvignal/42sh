/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:55:56 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/07 15:01:53 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int	expand_var_into_token(char **variables, t_token *token, t_shell *shell, int pos)
{
	int		i;
	char	*var_value;

	i = 0;
	while (variables[i])
	{
		if ((var_value = get_env_value(shell, variables[i])))
		{
			insert_into_token(token, var_value, pos);
			pos += ft_strlen(var_value);
		}
		i++;
	}
	return (pos);
}
