/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 07:03:18 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/26 22:08:54 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const char	*g_special_vars[] =\
{
	SPECIAL_PARAM_BANG,
	SPECIAL_PARAM_QMARK,
};

int			is_special_var(char name)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_special_vars) / sizeof(*g_special_vars))
	{
		if (g_special_vars[i][0] == name)
			return (1);
		++i;
	}
	return (0);
}

void		set_ret(t_shell *shell, t_ast *ast, int ret)
{
	char	*ret_str;

	if (ast)
		ast->ret = ret;
	if ((ret_str = ft_itoa(ret)))
	{
		set_special_var(&shell->vars, SPECIAL_PARAM_QMARK, ret_str);
		free(ret_str);
	}
}

void		set_bg_pid(t_shell *shell, pid_t pid)
{
	char	*ret_str;

	if ((ret_str = ft_itoa(pid)))
	{
		set_special_var(&shell->vars, SPECIAL_PARAM_BANG, ret_str);
		free(ret_str);
	}
}

int			set_special_var(t_var **vars, const char *name, const char *value)
{
	t_var		*var;

	if (!is_special_var(name[0]) && ft_strlen(name) == 1)
		return (1);
	if (!(var = get_var(*vars, name)))
	{
		if (!(var = alloc_var(name, value, 0)))
			return (1);
		add_to_vars(vars, var);
	}
	else
		concat_var(var, name, value);
	return (0);
}
