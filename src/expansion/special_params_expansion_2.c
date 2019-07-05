/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_params_expansion_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:14:59 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/05 15:16:07 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"

#include <unistd.h>

int	get_special_param_bang(t_shell *shell, char name)
{
	const char	*value;

	(void)name;
	value = get_var_value(get_var(shell->vars, SPECIAL_PARAM_BANG));
	return (add_string_to_exp_buff(&shell->exp_lexer, value));
}

int	get_special_param_qmark(t_shell *shell, char name)
{
	const char	*value;

	(void)name;
	value = get_var_value(get_var(shell->vars, SPECIAL_PARAM_QMARK));
	return (add_string_to_exp_buff(&shell->exp_lexer, value));
}

int	get_special_param_dollar(t_shell *shell, char name)
{
	char *pid_str;

	(void)name;
	if (!(pid_str = ft_itoa(getpid())))
		return (1);
	if (add_string_to_exp_buff(&shell->exp_lexer, pid_str))
	{
		free(pid_str);
		return (1);
	}
	free(pid_str);
	return (0);
}

int	get_special_param_hash(t_shell *shell, char name)
{
	char *argc_str;

	(void)name;
	if (!(argc_str = ft_itoa(shell->arg_file ? shell->arg_file->argc - 1 : 0)))
		return (1);
	if (add_string_to_exp_buff(&shell->exp_lexer, argc_str))
	{
		free(argc_str);
		return (1);
	}
	free(argc_str);
	return (0);
}

int	get_special_param_num(t_shell *shell, char name)
{
	const char	*argv;
	int			arg_num;

	arg_num = name - '0';
	if (shell->arg_file)
		argv = arg_num < shell->arg_file->argc ?
			shell->arg_file->argv[arg_num] : "";
	else
		argv = arg_num == 0 ? "42sh" : "";
	return (add_string_to_exp_buff(&shell->exp_lexer, argv));
}
