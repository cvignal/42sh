/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:50:57 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/18 14:00:30 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static int			is_a_separator(char a, char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == a)
			return (1);
		i++;
	}
	return (0);
}

static size_t		ft_lenword(const char *s, char *c)
{
	size_t	len;

	len = 0;
	while (!is_a_separator(*s, c) && *s)
	{
		len++;
		s++;
	}
	return (len);
}

static unsigned int	ft_nbwords(const char *s, char *c)
{
	unsigned int	nb;
	int				i;

	nb = 0;
	i = 0;
	while ((size_t)i < ft_strlen(s))
	{
		while (is_a_separator(s[i], c) && s[i])
			i++;
		if (ft_lenword(s + i, c))
		{
			i += ft_lenword(s + i, c);
			nb++;
		}
	}
	return (nb);
}

char				**ft_strsplit(char const *s, char *c)
{
	char			**tab;
	unsigned int	nb_words;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	nb_words = ft_nbwords((const char *)s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
	while (nb_words--)
	{
		while (is_a_separator(*s, c) && *s)
			s++;
		if (!(tab[i] = ft_strsub(s, 0, ft_lenword(s, c))))
			return (NULL);
		s += ft_lenword(s, c);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
