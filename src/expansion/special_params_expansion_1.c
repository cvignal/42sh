/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_params_expansion_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:08:57 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/10 15:52:02 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include <unistd.h>

static int	cond_fail(t_shell *shell, int *i)
{
	return (add_string_to_exp_buff(&shell->exp_lexer
				, shell->arg_file->argv[(*i)++])
			|| add_string_to_exp_buff(&shell->exp_lexer, shell->exp_lexer.ifs));
}

int			get_special_param_at(t_shell *shell, char name)
{
	int	i;

	(void)name;
	i = 1;
	if (shell->arg_file)
	{
		if (shell->exp_lexer.split)
		{
			while (i < shell->arg_file->argc)
				if (cond_fail(shell, &i))
					return (1);
		}
		else
		{
			while (i < shell->arg_file->argc)
			{
				if (add_string_to_exp_buff(&shell->exp_lexer
							, shell->arg_file->argv[i++]))
					return (1);
				if (i != shell->arg_file->argc)
					add_arg_to_array(&shell->exp_lexer, 0);
			}
		}
	}
	return (0);
}

int			get_special_param_star(t_shell *shell, char name)
{
	char	*ret;
	int		i;
	int		retval;

	retval = 0;
	(void)name;
	if (shell->arg_file)
	{
		i = 1;
		if (shell->exp_lexer.split)
			while (i < shell->arg_file->argc)
			{
				if (cond_fail(shell, &i))
					retval = 1;
			}
		else
		{
			if (!(ret = join_args(shell, shell->exp_lexer.ifs[0])))
				retval = 1;
			else if (add_string_to_exp_buff(&shell->exp_lexer, ret))
				retval = 1;
			free(ret);
		}
	}
	return (retval);
}
