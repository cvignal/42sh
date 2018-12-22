/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 10:29:40 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/22 19:03:50 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_line.h"
#include "libft.h"

static void	clear_cmd_line(t_cmdline *res)
{
	while (res->cursor < ft_strlen(res->str))
		ft_rightkey(res, NULL);
	ft_rightkey(res, NULL);
	while (res->cursor > 0)
		ft_backspace(res, NULL);
}

void		ft_hisdown(t_cmdline *res, t_shell *shell)
{
	t_list	*curr;
	int		i;

	if (!(curr = shell->history))
		return ;
	i = 0;
	if (res->his_pos > -1)
		res->his_pos--;
	while (i < res->his_pos && curr)
	{
		curr = curr->next;
		i++;
	}
	clear_cmd_line(res);
	if (res->his_pos > -1)
	{
		ft_printf("%s", curr->content);
		res->cursor = curr->content_size;
		ft_strdel(&res->str);
		res->str = ft_strdup(curr->content);
	}
}

void		ft_hisup(t_cmdline *res, t_shell *shell)
{
	t_list	*curr;
	int		i;

	clear_cmd_line(res);
	if (!(curr = shell->history))
		return ;
	i = 0;
	if (res->his_pos < (int)ft_lstlen(shell->history) - 1)
		res->his_pos++;
	while (i < res->his_pos && curr->next)
	{
		curr = curr->next;
		i++;
	}
	clear_cmd_line(res);
	ft_strdel(&res->str);
	res->str = ft_strdup(curr->content);
	ft_printf("%s", res->str);
	res->cursor = ft_strlen(res->str);
}
