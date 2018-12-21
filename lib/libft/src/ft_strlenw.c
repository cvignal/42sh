/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 15:32:26 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/25 11:29:16 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlenw(const wchar_t *s)
{
	size_t			len;
	unsigned int	pos;

	len = 0;
	pos = 0;
	while (s[pos])
	{
		len += ft_char_size_utf8(s[pos]);
		++pos;
	}
	return (len);
}
