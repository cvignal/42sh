/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:30:21 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/05 14:00:04 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "expand.h"
#include "libft.h"

int				clean_exit_exp_lexer(t_exp_lexer *lexer)
{
	t_exp_ss	*next;

	while (lexer->state && lexer->state->state != EXP_STATE_WORD)
	{
		next = lexer->state->next;
		if (lexer->state->buffer.buffer)
			free(lexer->state->buffer.buffer);
		free(lexer->state);
		lexer->state = next;
	}
	if (lexer->ret.data)
		ft_deltab(&lexer->ret.data);
	return (1);
}

void			reset_exp_lexer(t_shell *shell)
{
	const char	*ifs;

	shell->exp_lexer.split = 0;
	ft_bzero(&shell->exp_lexer.ret, sizeof(shell->exp_lexer.ret));
	ft_bzero(&shell->exp_lexer.state->buffer,
			sizeof(shell->exp_lexer.state->buffer));
	ifs = get_var_value(get_var(shell->vars, "IFS"));
	if (!ifs)
		ifs = DEFAULT_IFS;
	shell->exp_lexer.ifs = ifs;
}

static int		return_expand_params(t_command *cmd, t_array res)
{
	cmd->args_value = res.data;
	cmd->args_len = res.length;
	return (0);
}

int				expand_params(t_shell *shell, t_command *command, int mask)
{
	int		i;
	t_array	result;

	ft_bzero(&result, sizeof(result));
	if (command->args_value)
	{
		i = 0;
		while (command->args_value[i])
			free(command->args_value[i++]);
		free(command->args_value);
	}
	i = 0;
	while (command->args[i])
	{
		if (expand_main(shell, command->args[i], mask))
		{
			ft_deltab(&result.data);
			return (1);
		}
		ft_arraymerge(&result, &shell->exp_lexer.ret);
		free(shell->exp_lexer.ret.data);
		i++;
	}
	return (return_expand_params(command, result));
}
