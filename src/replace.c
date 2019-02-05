/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 12:16:25 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/05 12:32:02 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "libft.h"

int		remove_quotes(t_shell *shell, t_token *token)
{
	if (token->data[0] == 39)
	{
		token->data[token->len - 1] = 0;
		ft_memmove(token->data, token->data + 1, token->len - 1);
		return (0);
	}
	token->data[token->len - 1] = 0;
	ft_memmove(token->data, token->data + 1, token->len - 1);
	return (insert_var(shell, token));
}

int		insert_var(t_shell *shell, t_token *token)
{
	char	**variables;
	size_t	i;
	char	*var_value;
	size_t	pos;

	if (token->data[0] == 39 || token->data[0] == '"')
		return (remove_quotes(shell, token));
	if (!(variables = ft_strsplit(token->data, "$")))
		return (-1);
	i = 0;
	pos = 0;
	while(variables[i])
	{
		if ((var_value = get_env_value(shell, variables[i])))
		{
			insert_into_token(token, var_value, pos);
			pos += ft_strlen(var_value);
		}
		i++;
	}
	token->data[pos] = 0 ;
	return (1);
}

static int	insert_home(t_shell *shell, t_token *token, int pos)
{
	char	*home;

	home = get_env_value(shell, "HOME");
	if (home)
	{
		insert_into_token(token, home, pos);
		return (pos + ft_strlen(home));
	}
	return (pos);
}

int			replace_vars(t_shell *shell, t_token *token)
{
	int	pos;
	int	ret;

	if (token->data[0] == CHAR_TILDE)
	{
		if (insert_home(shell, token, 0) == -1)
			return (1);
	}
	pos = 0;
	while (token->data[pos])
	{
		if (token->data[pos] == CHAR_VAR && token->data[pos + 1])
		{
			if ((ret = insert_var(shell, token)) == -1)
				return (1);
			break ;
		}
		else
			++pos;
	}
	return (0);
}
