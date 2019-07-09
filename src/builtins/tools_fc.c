/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 11:34:34 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/09 16:59:35 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

int		fc_exec_ast(t_shell *shell, t_token *tokens, int flag)
{
	int	ret;
	t_ast	*ast;

	ret = 1;
	if (parse(shell, tokens) == PARSER_COMPLETE)
	{
		reset_terminal_mode(shell);
		ast = shell->parser.ret;
		exec_job(shell, ast, NULL);
		ret = ast->ret;
		close_everything(shell);
		ast->del(ast);
		shell->parser.ret = NULL;
	}
	if (!flag)
		add_to_history(shell->line.data, shell, 0);
	reset_terminal_mode(shell);
	raw_terminal_mode(shell);
	return (ret);
}

void	fc_free_shell(t_shell *shell, t_shell *new_shell)
{
	t_fd	*fd;
	t_fd	*next_fd;

	new_shell->jobs = shell->jobs;
	disable_signal(new_shell);
	free_line(&shell->line);
	lss_pop(&shell->lexer);
	pss_pop(&shell->parser);
	fd = shell->used_fd;
	while (fd)
	{
		next_fd = fd->next;
		free(fd);
		fd = next_fd;
	}
	free_token_list(shell->output);
	free_token_list(shell->current);
	if (shell->parser.ret)
	{
		shell->parser.ret->del(shell->parser.ret);
		shell->parser.ret = NULL;
	}
	exp_ss_pop(&shell->exp_lexer);
	reset_terminal_mode(shell);
}

int		fc_init_shell(t_shell *shell, t_shell *old_shell)
{
	ft_bzero(shell, sizeof(*shell));
	if (init_lexer(&shell->lexer) || init_parser(&shell->parser)
			|| init_exp_lexer(&shell->exp_lexer))
		return (1);
	shell->hash_table = old_shell->hash_table;
	if (!(shell->used_fd = (t_fd *)malloc(sizeof(t_fd))))
		return (1);
	shell->used_fd->fd = old_shell->fd_op;
	shell->used_fd->is_pipe = 0;
	shell->used_fd->next = NULL;
	ft_bzero(&shell->line, sizeof(shell->line));
	shell->vars = copy_vars(old_shell->vars, 0);
	shell->exec_vars = NULL;
	shell->fd_op = old_shell->fd_op;
	shell->prompt_len = 0;
	shell->win = old_shell->win;
	shell->history = old_shell->history;
	shell->fc_rec = 1;
	shell->rst_term = old_shell->rst_term;
	shell->raw_term = old_shell->raw_term;
	shell->jobs = old_shell->jobs;
	disable_signal(shell);
	return (0);
}

int		fc_cut_pattern(t_fc *cmd, char *str)
{
	size_t	len_old;
	size_t	len_new;

	len_new = ft_strlen(ft_strchr(str, '=') + 1);
	len_old = ft_strlen(str) - len_new;
	if (!len_new)
		cmd->new_p = ft_strnew(0);
	else
		cmd->new_p = ft_strsub(str, len_old, len_new);
	if (!len_old)
		cmd->old_p = ft_strnew(0);
	else
		cmd->old_p = ft_strsub(str, 0, len_old - 1);
	if (!cmd->old_p || !cmd->new_p)
		return (1);
	return (0);
}
