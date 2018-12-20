/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 01:25:16 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 12:07:02 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	size_s1;

	i = 0;
	size_s1 = 0;
	while (dest[size_s1])
		++size_s1;
	while (src[i])
	{
		dest[size_s1 + i] = src[i];
		++i;
	}
	dest[size_s1 + i] = '\0';
	return (dest);
}
