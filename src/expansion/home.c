/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:35:26 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/11 18:52:39 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "expand.h"
#include "libft.h"

static int	replace_home(t_exp_buff *buffer, const char *home)
{
	size_t			len;
	t_exp_buff		new_buffer;
	unsigned int	i;

	ft_bzero(&new_buffer, sizeof(new_buffer));
	len = ft_strlen(home);
	new_buffer.buffer = malloc(len + buffer->pos + 1);
	if (!new_buffer.buffer)
		return (1);
	new_buffer.alloc_size = len + buffer->pos + 1;
	new_buffer.buffer[0] = 0;
	while (*home)
		if (add_to_exp_buff(&new_buffer, *(home++)))
			return (1);
	i = 1;
	while (i < buffer->pos)
		if (add_to_exp_buff(&new_buffer, buffer->buffer[i++]))
			return (1);
	free(buffer->buffer);
	buffer->buffer = new_buffer.buffer;
	return (0);
}

int	expand_home(t_shell *shell, int *error)
{
	char	*home;

	if (shell->exp_lexer.buffer.buffer[0] == '~'
			&& (!shell->exp_lexer.buffer.buffer[1]
				|| shell->exp_lexer.buffer.buffer[1] == '/'))
	{
		home = get_env_value(shell, "HOME");
		if (home)
		{
			if (replace_home(&shell->exp_lexer.buffer, home))
			{
				*error = 1;
				return (1);
			}
		}
	}
	return (0);
}
