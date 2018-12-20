/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 01:35:55 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 12:08:30 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	size_dest;
	unsigned int	size_src;
	unsigned int	max_append;

	i = 0;
	size_dest = 0;
	size_src = 0;
	while (dest[size_dest])
		++size_dest;
	while (src[size_src])
		++size_src;
	max_append = size_dest >= size ? 0 : size - size_dest - 1;
	while (src[i] && i < max_append)
	{
		dest[size_dest + i] = src[i];
		++i;
	}
	dest[size_dest + i] = 0;
	if (size >= size_dest)
		return (size_src + size_dest);
	return (size_src + size);
}
