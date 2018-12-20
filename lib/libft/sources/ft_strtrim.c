/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:03:23 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 18:37:19 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

static int	get_last_pos(char const *s)
{
	int		pos;

	pos = ft_strlen(s) - 1;
	while (pos > 0)
	{
		if (!is_whitespace(s[pos]))
			return (pos + 1);
		--pos;
	}
	return (pos > 0 ? pos : 0);
}

char		*ft_strtrim(char const *s)
{
	char			*new_s;
	unsigned int	pos_s;
	unsigned int	pos_new_s;
	unsigned int	last_pos;

	if (!s)
		return (NULL);
	pos_s = 0;
	pos_new_s = 0;
	while (is_whitespace(s[pos_s]))
		++pos_s;
	last_pos = get_last_pos(s);
	new_s = malloc(sizeof(*new_s) * (last_pos - pos_s + 1));
	if (new_s)
	{
		while (pos_s < last_pos)
			new_s[pos_new_s++] = s[pos_s++];
		new_s[pos_new_s] = 0;
	}
	return (new_s);
}
