/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_set_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 00:50:40 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/24 17:31:35 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "libft.h"

static int	var_cmp(void *a, void *b)
{
	return (ft_strcmp( ((t_var *)a)->var, ((t_var *)b)->var));
}

t_var		*vars_to_array(t_var *vars)
{
	size_t			len;
	t_var			*iter;
	t_var			*res;
	unsigned int	i;

	len = 0;
	iter = vars;
	while (iter)
	{
		++len;
		iter = iter->next;
	}
	if (!(res = malloc(sizeof(*res) * len)))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		return (NULL);
	}
	i = 0;
	while (vars)
	{
		ft_memcpy(res + i++, vars, sizeof(*vars));
		vars = vars->next;
	}
	ft_quicksort(res, sizeof(*res), len, &var_cmp);
	return (res);
}
