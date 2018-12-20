/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 01:28:02 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 12:08:40 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, const char *src, int n)
{
	int	i;
	int	size_s1;

	i = 0;
	size_s1 = 0;
	while (dest[size_s1])
		++size_s1;
	while (src[i] && n)
	{
		dest[size_s1 + i] = src[i];
		++i;
		--n;
	}
	dest[size_s1 + i] = '\0';
	return (dest);
}
