/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_params_expansion_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marin </var/spool/mail/marin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:18:50 by marin             #+#    #+#             */
/*   Updated: 2019/06/20 20:10:32 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include <unistd.h>

int	get_special_param_at(t_shell *shell)
{
	int	i;

	i = 1;
	if (shell->arg_file)
	{
		if (shell->exp_lexer.split)
		{
			while (i < shell->arg_file->argc)
				if (add_string_to_exp_buff(&shell->exp_lexer, shell->arg_file->argv[i++])
				 ||add_string_to_exp_buff(&shell->exp_lexer, shell->exp_lexer.ifs))
					return (1);
		}
		else
		{
			while (i < shell->arg_file->argc)
			{
				if (add_string_to_exp_buff(&shell->exp_lexer, shell->arg_file->argv[i++]))
					return (1);
				if (i != shell->arg_file->argc)
					add_arg_to_array(&shell->exp_lexer, 0);
			}
		}
	}
	return 0;
}

int	get_special_param_star(t_shell *shell)
{
	char	*ret;
	int	i;
	int	retval;

	retval = 0;
	if (shell->arg_file)
	{
		i = 1;
		if (shell->exp_lexer.split)
			while (i < shell->arg_file->argc)
			{
				if (add_string_to_exp_buff(&shell->exp_lexer, shell->arg_file->argv[i++])
				|| add_string_to_exp_buff(&shell->exp_lexer, shell->exp_lexer.ifs))
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

int	get_special_param_dollar(t_shell *shell)
{
	char *pid_str;

	if (!(pid_str = ft_itoa(getpid())))
		return (1);
	if (add_string_to_exp_buff(&shell->exp_lexer, pid_str)){
		free(pid_str);
		return (1);
	}
	free(pid_str);
	return (0);
}

int	get_special_param_hash(t_shell *shell)
{
	char *argc_str;
	
	if (!(argc_str = ft_itoa(shell->arg_file ? shell->arg_file->argc - 1: 0)))
		return (1);
	if (add_string_to_exp_buff(&shell->exp_lexer, argc_str))
	{
		free(argc_str);
		return (1);
	}
	free(argc_str);
	return (0);
}

int	get_special_param_zero(t_shell *shell)
{
	const char	*prog_name;

	prog_name = shell->arg_file ? shell->arg_file->argv[0] : "42sh";
	return (add_string_to_exp_buff(&shell->exp_lexer, prog_name));
}
