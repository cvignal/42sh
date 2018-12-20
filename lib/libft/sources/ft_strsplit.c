/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:11:54 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 18:37:02 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static unsigned int	get_word_count(char const *s, char c)
{
	unsigned int	pos;
	unsigned int	word_count;
	int				in_word;

	pos = 0;
	in_word = 0;
	word_count = 0;
	while (s[pos])
	{
		if (s[pos] != c)
		{
			if (!in_word)
				++word_count;
			in_word = 1;
		}
		else
			in_word = 0;
		++pos;
	}
	return (word_count);
}

static unsigned int	get_word_length(char const *s, unsigned int pos, char c)
{
	size_t	len;

	len = 0;
	while (s[pos + len] && s[pos + len] != c)
		++len;
	return (len);
}

static int			copy_word(char **mem, char const *s,
		unsigned int pos, char c)
{
	size_t			len;
	unsigned int	i;

	len = get_word_length(s, pos, c);
	*mem = malloc(sizeof(**mem) * (len + 1));
	if (!*mem)
		return (-1);
	i = 0;
	while (len)
	{
		(*mem)[i++] = s[pos];
		--len;
		++pos;
	}
	(*mem)[i] = 0;
	while (s[pos] && s[pos] == c)
		++pos;
	return (pos);
}

static char			**exit_free(char **arr, unsigned int word)
{
	while (word)
		free(arr[--word]);
	free(arr);
	return (NULL);
}

char				**ft_strsplit(char const *s, char c)
{
	char			**arr;
	unsigned int	word_count;
	unsigned int	word;
	int				pos;

	if (!s)
		return (NULL);
	word_count = get_word_count(s, c);
	arr = malloc(sizeof(*arr) * (word_count + 1));
	if (!arr)
		return (NULL);
	word = 0;
	pos = 0;
	while (s[pos] && s[pos] == c)
		++pos;
	while (word < word_count)
	{
		pos = copy_word(arr + word, s, pos, c);
		if (pos < 0)
			return (exit_free(arr, word));
		++word;
	}
	arr[word] = NULL;
	return (arr);
}
