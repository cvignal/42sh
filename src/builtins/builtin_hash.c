/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 13:34:20 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/20 17:18:34 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	print_hash_table(t_shell *shell)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!shell->hash_table)
		return (1);
	while (i < HASH_TABLE_SIZE)
	{
		if (shell->hash_table[i])
		{
			flag = 1;
			print_rec_tree(shell->hash_table[i]);
		}
		i++;
	}
	if (!flag)
		ft_dprintf(2, "hash: hash table empty\n");
	return (0);
}

static int	invalid_option_hash(char c)
{
	ft_dprintf(2, "%s: hash: %c: invalid option\n", EXEC_NAME, c);
	ft_dprintf(2, "hash: usage: hash [-r] [name ...]\n");
	return (-1);
}

static int	parse_options(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i] && !ft_strequ(args[i], "--") && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j])
		{
			if (args[i][j] != 'r')
				return (invalid_option_hash(args[i][j]));
			j++;
		}
		i++;
	}
	return (i - 1);
}

static void	remove_hashtable(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->hash_table)
		return ;
	while (i < HASH_TABLE_SIZE)
	{
		if (shell->hash_table[i])
		{
			free_hbt(shell->hash_table[i]);
			shell->hash_table[i] = NULL;
		}
		i++;
	}
}

int			builtin_hash(t_shell *shell, char **args)
{
	int		i;
	char	*cmd;

	if ((i = parse_options(args)) == -1)
		return (1);
	if (i && shell->hash_table)
		remove_hashtable(shell);
	i++;
	if (ft_strequ(args[i], "--"))
		i++;
	if (!args[i])
		print_hash_table(shell);
	while (args[i])
	{
		if (is_builtin(args[i]) || ft_strchr(args[i], '/'))
			;
		else if ((cmd = hbt_command(shell, args[i])))
			;
		else
			ft_dprintf(2, "%s: hash: %s: not found\n", EXEC_NAME, args[i]);
		i++;
	}
	return (0);
}
