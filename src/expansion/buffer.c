/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:14:35 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/03 10:54:11 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "expand.h"
#include "libft.h"

static int	realloc_exp_buff(t_exp_buff *buffer, size_t new_size)
{
	char			*new_buffer;
	unsigned int	i;

	new_buffer = malloc(sizeof(*new_buffer) * (new_size + 1));
	if (!new_buffer)
		return (1);
	i = 0;
	while (i < buffer->pos)
	{
		new_buffer[i] = buffer->buffer[i];
		++i;
	}
	free(buffer->buffer);
	buffer->buffer = new_buffer;
	buffer->alloc_size = new_size;
	ft_bzero(buffer->buffer + buffer->pos, sizeof(*buffer->buffer)
			* (buffer->alloc_size - buffer->pos + 1));
	return (0);
}

static int	add_arg_to_array(t_exp_lexer *lexer, char c)
{
	t_exp_buff	*buffer;
	int			ret;
	char		*empty_line;

	ret = 0;
	buffer = &lexer->state->buffer;
	if (buffer->buffer)
	{
		if (ft_arrayadd(&lexer->ret, buffer->buffer))
			ret = 1;
		else
		{
			free(buffer->buffer);
			ft_bzero(buffer, sizeof(*buffer));
		}
	}
	else if (!ft_strchr(DEFAULT_IFS, c))
	{
		if (!(empty_line = ft_strdup("")))
			ret = 1;
		else
			ft_arrayadd(&lexer->ret, empty_line);
	}
	return (ret);
}

int			add_char_to_exp_buff(t_exp_lexer *lexer, char c)
{
	t_exp_buff	*buffer;

	buffer = &lexer->state->buffer;
	if (lexer->state->state == EXP_STATE_WORD && lexer->split
			&& ft_strchr(lexer->ifs, c))
	{
		if (add_arg_to_array(lexer, c))
			return (1);
	}
	else
	{
		if (buffer->pos + 1 >= buffer->alloc_size)
		{
			if (realloc_exp_buff(buffer,
						buffer->alloc_size + EXP_BUFFER_ALLOC_SIZE))
				return (1);
		}
		buffer->buffer[buffer->pos++] = c;
	}
	return (0);
}

int			add_string_to_exp_buff(t_exp_lexer *lexer, const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		add_char_to_exp_buff(lexer, s[i]);
		++i;
	}
	return (0);
}
