/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:23:40 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/18 17:47:49 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "expand.h"

t_list	*exp_globbing(t_shell *shell, char *pattern)
{
	t_list			*ret;
	t_list			*paths;
	char			*last_dir;
	t_list			*new;
	char			*path_pattern;

	ret = NULL;
	if (!(last_dir = gb_last_dir(pattern)))
		return (NULL);
	if (!(path_pattern = gb_path_pattern(pattern)))
		return (NULL);
	if ((gb_recur_paths(last_dir, &paths)))
		return (NULL);
	while (paths)
	{
		if (ft_match(path_pattern, paths->content))
		{
			if (!(new = ft_lsnew(paths->content, ft_strlen(paths->content) + 1)))
				return (NULL);
			ft_lstadd(&ret, new);
		}
		paths = paths->next;
	}
	return (ret);
}
