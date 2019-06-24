/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marin </var/spool/mail/marin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:35:55 by marin             #+#    #+#             */
/*   Updated: 2019/06/24 08:32:31 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include <unistd.h>

typedef struct		s_special_param
{
	char	*name;
	int	(*f)(t_shell *, char);
}			t_special_param;


static const t_special_param	g_special_params[16] = \
{
	{SPECIAL_PARAM_AT, &get_special_param_at},
	{SPECIAL_PARAM_STAR, &get_special_param_star},
	{SPECIAL_PARAM_BANG, &get_special_param_bang},
	{SPECIAL_PARAM_ZERO, &get_special_param_num},
	{SPECIAL_PARAM_ONE, &get_special_param_num},
	{SPECIAL_PARAM_TWO, &get_special_param_num},
	{SPECIAL_PARAM_THREE, &get_special_param_num},
	{SPECIAL_PARAM_FIVE, &get_special_param_num},
	{SPECIAL_PARAM_SIX, &get_special_param_num},
	{SPECIAL_PARAM_SEVEN, &get_special_param_num},
	{SPECIAL_PARAM_EIGHT, &get_special_param_num},
	{SPECIAL_PARAM_NINE, &get_special_param_num},
	{SPECIAL_PARAM_FOUR, &get_special_param_num},
	{SPECIAL_PARAM_DOLLAR, &get_special_param_dollar},
	{SPECIAL_PARAM_QMARK, &get_special_param_qmark},
	{SPECIAL_PARAM_HASH, &get_special_param_hash},
};

int			is_special_param(char name)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_special_params) / sizeof(*g_special_params))
	{
		if (g_special_params[i].name[0] == name)
			return (1);
		++i;
	}
	return (0);
}

int	expand_special_params(t_shell *shell, char name)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_special_params) / sizeof(*g_special_params))
	{
		if (g_special_params[i].name[0] == name)
			return (g_special_params[i].f(shell, name));
		++i;
	}
	return (0);
}
