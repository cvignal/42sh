/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:48:05 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 14:46:38 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "minishell.h"

t_key	special_keys[] =
{
	{LEFT_ARROW, &ft_leftkey},
	{RIGHT_ARROW, &ft_rightkey},
	{BACKSPACE, &ft_backspace},
	{TAB_KEY, &ft_tab}
};

int	is_a_special_key(char *buf)
{
		return (!(*buf > 31 && *buf < 127));
}

int		ft_printchar(int c)
{
		return (write(1, &c, 1));
}

void	apply_key(char *buf, t_cmdline *res)
{
	int		i;
	size_t	len;

	i = 0;
	if (*buf == 127)
		ft_backspace(res);
	while (i < 4)
	{
		len = ft_strlen(special_keys[i].value);
		if (ft_strnequ(special_keys[i].value, buf, len))
			special_keys[i].f(res);
		i++;
	}
}
