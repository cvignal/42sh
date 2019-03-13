/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:59:25 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/13 16:59:40 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

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
	if (!(ret = ft_strjoin_free("/tmp/", ret, 2)))
		return (NULL);
	return (ret);
}

int					fc_open_file(t_fc *cmd, t_shell *shell, t_tmpfile *file)
{
	int	i;

	if (!(file->name = fc_generate_hash(cmd, shell->history)))
		return (1);
	if ((file->fd = open(file->name, O_RDWR | O_APPEND | O_CREAT, 0644)) == -1)
		return (1);
	i = cmd->i_first;
	while (i < shell->history->length && i <= cmd->i_last)
		ft_dprintf(file->fd, "%s\n", shell->history->data[i++]);
	if (close(file->fd) == -1)
		return (1);
	return (0);
}
