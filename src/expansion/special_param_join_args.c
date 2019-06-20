/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_param_join_args.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marin </var/spool/mail/marin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:09:43 by marin             #+#    #+#             */
/*   Updated: 2019/06/08 17:11:31 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include <unistd.h>

static int	args_malloc_size(t_shell *shell)
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
