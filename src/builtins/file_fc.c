/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:59:25 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/09 17:24:40 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "shell.h"
#include "libft.h"

unsigned long long	ft_djbtwo_hash(const char *str)
{
	unsigned long long	hash;
	int					i;
	char				*cpy;

	cpy = (char *)str;
	hash = 5381;
	i = 0;
	while (cpy[i])
	{
		hash = ((hash << 5) + hash) + cpy[i];
		i++;
	}
	return (hash);
}

char				*fc_generate_hash(t_fc *cmd, t_array *history)
{
	unsigned long long	hash;
	char				*ret;
	int					i;

	hash = ft_djbtwo_hash(getlogin());
	i = cmd->i_first;
	while (i < history->length && i <= cmd->i_last)
		hash += ft_djbtwo_hash(history->data[i++]);
	hash += getpid();
	if (!(ret = ft_ultoa_base(hash, 16)))
		return (NULL);
	if (!(ret = ft_strjoin_free("/tmp/", ret, 2)))
		return (NULL);
	return (ret);
}

int					fc_open_file(t_fc *cmd, t_shell *shell, t_tmpfile *file)
{
	int			i;

	if (!(file->name = fc_generate_hash(cmd, shell->history)))
		return (1);
	if ((file->fd = open(file->name, O_RDWR | O_CREAT | O_EXCL, 0644)) == -1)
	{
		free(file->name);
		return (1);
	}
	i = cmd->i_first;
	while (i < shell->history->length && i <= cmd->i_last)
		ft_dprintf(file->fd, "%s\n", shell->history->data[i++]);
	if (close(file->fd) == -1)
		return (1);
	return (0);
}

int					fc_find_editor(t_fc *cmd, char **args, t_shell *shell)
{
	char	*editor;

	if (cmd->editor)
	{
		if (!(args[0] = ft_strdup(cmd->editor)))
			return (1);
	}
	else if ((editor = (char *)get_var_value(get_var(shell->vars, "FCEDIT")))
			|| (editor = (char *)get_var_value(get_var(shell->vars, "EDITOR"))))
	{
		if (!(args[0] = ft_strdup(editor)))
			return (1);
		if (!(cmd->editor = ft_strdup(editor)))
			return (1);
	}
	else
	{
		if (!(args[0] = ft_strdup("vim")))
			return (1);
	}
	return (0);
}

int					fc_open_editor(t_fc *cmd, t_tmpfile *file, t_shell *shell)
{
	char	*editor;
	char	*str;

	if (ft_strchr(cmd->flags, 'e') && !cmd->editor)
		return (usage_fc(1, 'e'));
	if (fc_find_editor(cmd, &editor, shell))
		return (1);
	if (!(str = ft_strjoin_free(editor, " ", 1)))
		return (1);
	if (!(str = ft_strjoin_free(str, file->name, 1)))
		return (1);
	fc_exec_line(str, shell, 1);
	return (0);
}
