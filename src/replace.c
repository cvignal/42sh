/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 12:16:25 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/07 17:24:36 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "libft.h"

int			remove_quotes(t_shell *shell, t_token *token)
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

int			insert_var(t_shell *shell, t_token *token)
{
	char	**variables;
	size_t	pos;
	int		end_dollar;

	if (token->data[0] == 39 || token->data[0] == '"')
		return (remove_quotes(shell, token));
	if (!(variables = ft_strsplit(token->data, "$")))
		return (-1);
	pos = 0;
	end_dollar = 0;
	if (token->data[token->len - 1] == CHAR_VAR)
		end_dollar = 1;
	if (token->data[0] != CHAR_VAR)
	{
		insert_into_token(token, variables[0], pos);
		pos += ft_strlen(variables[0]);
	}
	pos = expand_var_into_token(variables, token, shell, pos);
	if (end_dollar)
		insert_into_token(token, "$", pos++);
	token->data[pos] = 0;
	ft_deltab(&variables);
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

int			expand_vars(t_shell *shell, char *arg)
{
	int	pos;
	int	ret;

	pos = 0;
	while (arg[pos])
	{
		if (arg[pos] == '\\' && arg[pos + 1] && (arg[pos + 1] == CHAR_VAR
					|| arg[pos + 1] == CHAR_HOME))
			remove_backslash();
		else if (arg[pos] == CHAR_VAR && token->data[pos + 1])
		{
			if ((ret = insert_var(shell, token)) == -1)
				return (1);
			break ;
		}
		else if (arg[pos] == CHAR_HOME)
		{
			if ((ret = insert_var(shell, arg) == -1))
				return (1);
			break ;
		}
		else
			++pos;
	}
	return (0);
}
