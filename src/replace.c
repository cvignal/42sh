/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 12:16:25 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 18:43:56 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "libft.h"

static int	insert_var(t_shell *shell, t_token *token, int pos)
{
	char	*var;

	token->len = pos;
	var = get_env_value(shell, token->data + token->len + 1);
	if (var)
	{
		while (*var)
			if (add_to_token(token, *var++))
				return (-1);
		if (add_to_token(token, 0))
			return (-1);
	}
	else
		token->data[pos] = 0;
	return (token->len);
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
			if ((ret = insert_var(shell, token, pos)) == -1)
				return (1);
			break ;
		}
		else
			++pos;
	}
	return (0);
}
