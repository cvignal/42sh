/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:52:57 by agrouard          #+#    #+#             */
/*   Updated: 2019/06/28 19:26:56 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"

static char *redir_to_string(t_redir *redir)
{
	static char *chars[] = {"<", "<&-", "<&", "<<",
		">", ">&", ">&-", ">&", ">>", "<>"};
	int			index;
	char		*str;

	index = redir->type - TT_REDIR_L;
	str = ft_strjoin_free(ft_itoa(redir->in), chars[index], 1);
	if (redir->target)
		str = ft_strjoin_free(str, redir->target, 1);
	else if (redir->type == TT_REDIR_L_COMP ||
			redir->type == TT_REDIR_R_COMP)
		str = ft_strjoin_free(str, ft_itoa(redir->out), 1 | 2);
	return (str);
}

static char	*simple_to_string(t_ast *ast)
{
	size_t		i;
	char		*str;
	t_command	*cmd;
	t_redir		*redir;

	i = 0;
	cmd = (t_command *)ast->data;
	str = ft_strdup(cmd->args[i]);
	while (++i < cmd->args_len)
		str = ft_strcjoin_free(str, ' ', cmd->args[i], 1);
	redir = ast->redir_list;
	while (redir)
	{
		str = ft_strcjoin_free(str, ' ', redir_to_string(redir), 1 | 2);
		redir = redir->next;		
	}
	return (str);
}

static char	*condition_to_string(t_ast *ast)
{
	char	*res;

	res = ast_to_string(ast->left);
	res = ft_strjoin_free(res, ast->type == TT_AND ? " && " : " || ", 1);
	return (ft_strjoin_free(res, ast_to_string(ast->right), 1 | 2));
}

char		*ast_to_string(t_ast *ast)
{
	if (!ast)
		return (NULL);
	if (ast->type == TT_CMD)
		return (simple_to_string(ast));
	if (ast->type == TT_AND)
		return (condition_to_string(ast));
	if (ast->type == TT_OR)
		return (condition_to_string(ast));
	return (NULL);
}
