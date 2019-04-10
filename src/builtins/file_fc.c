/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:59:25 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/30 18:58:47 by cvignal          ###   ########.fr       */
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
	int					c;

	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
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
	if (!(ret = ft_ultoa_base(hash, 16)))
		return (NULL);
	if (!(ret = ft_strjoin_free("/tmp/folder_fc_builtin/", ret, 2)))
		return (NULL);
	return (ret);
}

int					fc_open_file(t_fc *cmd, t_shell *shell, t_tmpfile *file)
{
	int			i;
	struct stat	st;

	if (stat("/tmp/folder_fc_builtin", &st) == -1)
		mkdir("/tmp/folder_fc_builtin", 0755);
	if (!(file->name = fc_generate_hash(cmd, shell->history)))
		return (1);
	if ((file->fd = open(file->name, O_RDWR | O_CREAT | O_EXCL, 0644)) == -1)
		return (1);
	i = cmd->i_first;
	while (i < shell->history->length && i <= cmd->i_last)
		ft_dprintf(file->fd, "%s\n", shell->history->data[i++]);
	if (close(file->fd) == -1)
		return (1);
	return (0);
}

int					fc_find_editor(t_fc *cmd, char **args)
{
	if (cmd->editor)
	{
		if (!(args[0] = ft_strdup(cmd->editor)))
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
	char	**args;
	int		ret;

	if (!(args = (char**)malloc(sizeof(char*) * 3)))
		return (1);
	if (fc_find_editor(cmd, args))
	{
		ft_deltab(&args);
		return (1);
	}
	if (!(args[1] = ft_strdup(file->name)))
	{
		ft_deltab(&args);
		return (1);
	}
	args[2] = NULL;
	ret = exec_from_char(shell, args, shell);
	ft_deltab(&args);
	return (ret);
}
