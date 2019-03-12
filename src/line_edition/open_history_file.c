/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_history_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:28:57 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/12 11:29:45 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

static const char	*g_default_home_value = "/Users/cvignal";

int		open_history_file(t_shell *shell)
{
	char	*file;
	char	*home_dir;
	int		fd;

	if (!(home_dir = get_env_value(shell, "HOME")))
		home_dir = (char *)g_default_home_value;
	if (!(file = ft_strjoin(home_dir, "/.shperso_history")))
		return (-1);
	if ((fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644)) == -1)
	{
		ft_strdel(&file);
		if (!(file = ft_strjoin(g_default_home_value, "/.shperso_history")))
			return (-1);
		fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	ft_strdel(&file);
	return (fd);
}
