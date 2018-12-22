/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:48:05 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/22 13:55:38 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "minishell.h"
#include "fill_line.h"

t_key	g_special_keys[] =
{
	{LEFT_ARROW, &ft_leftkey},
	{RIGHT_ARROW, &ft_rightkey},
	{BACKSPACE, &ft_backspace},
	{TAB_KEY, &ft_tab},
	{DOWN_ARROW, &ft_hisdown},
	{UP_ARROW, &ft_hisup}
};

int		is_a_special_key(char *buf)
{
	return (!(*buf > 31 && *buf < 127));
}

int		ft_printchar(int c)
{
	return (write(1, &c, 1));
}

void	apply_key(char *buf, t_cmdline *res, t_shell *shell)
{
	int		i;
	size_t	len;

	i = 0;
	if (*buf == 127)
		ft_backspace(res, shell);
	while (i < 6)
	{
		len = ft_strlen(g_special_keys[i].value);
		if (ft_strnequ(g_special_keys[i].value, buf, len))
			g_special_keys[i].f(res, shell);
		i++;
	}
}
