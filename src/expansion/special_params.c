/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marin </var/spool/mail/marin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:35:55 by marin             #+#    #+#             */
/*   Updated: 2019/06/03 11:28:42 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include <unistd.h>

//TODO: cleaning

typedef struct		s_special_param
{
	char	name;
	int	(*f)(t_shell *shell);
}			t_special_param;


int	args_malloc_size(t_shell *shell)
{
	int	size;
	int	i;

	i = 1;
	size = shell->arg_file->argc;
	while (i < shell->arg_file->argc)
		size += ft_strlen(shell->arg_file->argv[i++]);
	return (size);
}

char	*join_args(t_shell *shell, char separator)
{
	char	*ret;
	int	ret_size;
	int	i;

	i = 1;
	ret_size = args_malloc_size(shell);
	if (!(ret = malloc(ret_size)))
		return (NULL);
	ft_memset(ret, 0, ret_size);
	while (i < shell->arg_file->argc)
	{
		ft_strcat(ret, shell->arg_file->argv[i++]);
		if (i != shell->arg_file->argc)
			ft_strncat(ret, &separator, 1);
	}
	return ret;

}

int	get_special_param_at(t_shell *shell)
{
	int	i;

	i = 1;
	if (shell->exp_lexer.split)
		while (i < shell->arg_file->argc)
		{
			add_string_to_exp_buff(&shell->exp_lexer, shell->arg_file->argv[i++]);
			add_string_to_exp_buff(&shell->exp_lexer, shell->exp_lexer.ifs);
		}
	else
	{
		while (i < shell->arg_file->argc)
		{
			add_string_to_exp_buff(&shell->exp_lexer, shell->arg_file->argv[i++]);
			if (i != shell->arg_file->argc)
				add_arg_to_array(&shell->exp_lexer, 0);
		}
	}
	return 0;
}

int	get_special_param_star(t_shell *shell)
{
	char	*ret;
	int	i;

	i = 1;
	if (shell->exp_lexer.split)
		while (i < shell->arg_file->argc)
		{
			add_string_to_exp_buff(&shell->exp_lexer, shell->arg_file->argv[i++]);
			add_string_to_exp_buff(&shell->exp_lexer, shell->exp_lexer.ifs);
		}
	else
	{
		//TODO: make sure the return in the good one
		if (!(ret = join_args(shell, shell->exp_lexer.ifs[0])))
			return (1);
		//TODO: protect this?
		add_string_to_exp_buff(&shell->exp_lexer, ret);
		free(ret);
	}
	return (0);
}
int	get_special_param_bang(t_shell *shell)
{
	(void) shell;
	return (0);
}
int	get_special_param_dollar(t_shell *shell)
{
	char *pid_str;

	if (!(pid_str = ft_itoa(getpid())))
		return (1);
	add_string_to_exp_buff(&shell->exp_lexer, pid_str);
	return (0);
}
int	get_special_param_hash(t_shell *shell)
{
	char *argc_str;

	if (!(argc_str = ft_itoa(shell->arg_file ? shell->arg_file->argc - 1: 0)))
		return (1);
	add_string_to_exp_buff(&shell->exp_lexer, argc_str);
	return (0);
}

static const t_special_param	g_special_params[5] = \
{
	{SPECIAL_PARAM_AT, &get_special_param_at},
	{SPECIAL_PARAM_STAR, &get_special_param_star},
	{SPECIAL_PARAM_BANG, &get_special_param_bang},
	{SPECIAL_PARAM_DOLLAR, &get_special_param_dollar},
	{SPECIAL_PARAM_HASH, &get_special_param_hash}
};

int			is_special_param(char name)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_special_params) / sizeof(*g_special_params))
	{
		if (g_special_params[i].name == name)
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
		if (g_special_params[i].name == name)
			return (g_special_params[i].f(shell));
		++i;
	}
	return (0);
}
