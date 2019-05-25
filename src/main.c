/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <gchainet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:14:15 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/25 13:24:25 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "shell.h"
#include "ast.h"
#include "libft.h"
#include "fill_line.h"

static const t_readline	g_functions[3] =\
{
	{0, &fill_line},
	{1, &alt_fill_line},
	{2, &read_from_file} 
};

static void				exec_ast(t_shell *shell, t_token *tokens)
{
	t_ast	*ast;

	parse(shell, tokens);
	if (shell->parser.ret_status == PARSER_COMPLETE)
	{
		ast = shell->parser.ret;
		ast->exec(shell, ast);
		close_everything(shell);
		wait_loop(shell, ast);
		ast->del(ast);
		shell->parser.ret = NULL;
	}
	else if (shell->parser.ret_status == PARSER_ERROR)
		set_ret(shell, NULL, 2);
	add_to_history(shell->line.data, shell, 0);
	reset_terminal_mode(shell);
	raw_terminal_mode(shell);
	print_prompt(shell, 0);
}

void	set_shell_input_file(t_shell *shell, int ac, char **av)
{
	if ((shell->arg_file = malloc(sizeof(t_arg_file))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		exit(127);
	}
	shell->arg_file->filename = av[0];
	shell->arg_file->argv = av;
	shell->arg_file->argc = ac;
	if (!access(shell->arg_file->filename, F_OK))
	{
		if (!access(shell->arg_file->filename, R_OK))
		{
			if ((shell->arg_file->fd = open(shell->arg_file->filename, O_RDONLY)) != -1)
				return;
			//TODO permission denied message	
			ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
			exit(127);
		}
		//TODO: file not found message 
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		exit(127);
	}
}

void	parse_args(t_shell *shell, int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac && *av[i] == '-')
		i++; // will deal with shell params later
	if (ac != i)
		set_shell_input_file(shell, ac - i, &av[i]);
}

int						main(int ac, char **av, const char **environ)
{
	t_shell		shell;
	t_token		*tokens;
	int			ret;

	if (init_shell(&shell, environ))
		return (free_shell(&shell));
	parse_args(&shell, ac, av);
	ret = check_validity(&shell);
	set_special_var(&shell.vars, SPECIAL_VAR_RET, "0");
	print_prompt(&shell, 0);
	disable_signal(&shell);
	while (!g_functions[ret].f(&shell))
	{
		if (!(tokens = lex(&shell, shell.line.data)))
		{
			add_to_history(shell.line.data, &shell, 1);
			print_prompt(&shell, 1);
		}
		else
			exec_ast(&shell, tokens);
		free_line(&shell.line);
		raw_terminal_mode(&shell);
	}
	builtin_exit(&shell, NULL);
}
