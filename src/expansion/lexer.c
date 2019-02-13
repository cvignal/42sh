/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 21:18:39 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/12 21:12:22 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "expand.h"
#include "libft.h"

static char	*clean_exit(t_exp_lexer *lexer, int *error)
{
	if (lexer->buffer.pos)
		free(lexer->buffer.buffer);
	if (lexer->var.pos)
		free(lexer->var.buffer);
	*error = 1;
	return (NULL);
}

static char	*expand(t_shell *shell, char *arg, int *error)
{
	int	i;
	int	ret;

	ft_bzero(&shell->exp_lexer.buffer, sizeof(shell->exp_lexer.buffer));
	ft_bzero(&shell->exp_lexer.var, sizeof(shell->exp_lexer.var));
	i = 0;
	while (arg[i])
	{
		ret = shell->exp_lexer.methods[shell->exp_lexer.state->state]
			[(int)arg[i]](shell, &shell->exp_lexer, arg[i]);
		if (ret & EXP_LEXER_RET_ERROR)
			return (clean_exit(&shell->exp_lexer, error));
		if (ret & EXP_LEXER_RET_CONT)
			++i;
	}
	if (shell->exp_lexer.state->state == EXP_STATE_VAR)
		if (exp_lexer_cut_var(shell, &shell->exp_lexer, 0)
				& EXP_LEXER_RET_ERROR)
			return (clean_exit(&shell->exp_lexer, error));
	if (shell->exp_lexer.buffer.buffer)
		expand_home(shell, error);
	return (shell->exp_lexer.buffer.buffer);
}

int			expand_params(t_shell *shell, t_command *command)
{
	int		i;
	int		j;
	int		error;

	i = 1;
	j = 0;
	while (command->args[i])
	{
		error = 0;
		if (command->args_value[i - j])
			free(command->args_value[i - j]);
		command->args_value[i - j] = expand(shell, command->args[i], &error);
		if (error)
		{
			ft_dprintf(2, "%s: unable to allocate memory\n", EXEC_NAME);
			return (1);
		}
		if (!command->args_value[i - j])
			++j;
		++i;
	}
	command->args_value[i - j] = NULL;
	return (0);
}