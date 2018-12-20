/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:40:31 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 19:29:57 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "libft.h"

# define LEFT_ARROW "\033[D"
# define RIGHT_ARROW "\033[C"
# define UP_ARROW "\033[A"
# define DOWN_ARROW "\033[B"
# define HOME_KEY "\033[H"
# define END_KEY "\033[F"
# define PAGE_UP "\033[5~"
# define PAGE_DOWN "\033[6~"
# define DEL_KEY "\033[3~"
# define CLEAR_KEY "\033"
# define TAB_KEY "\t"
# define CTRL_D "\x4\0\0\0\0\0"
# define CTRL_R "\x12\0\0\0\0\0"
# define RETURN "\n"
# define BACKSPACE "\b"

typedef struct	s_cmdline
{
	char	*str;
	size_t	cursor;
}				t_cmdline;

typedef struct	s_key
{
	char	*value;
	void	(*f)(t_cmdline *res);
}				t_key;

char			**copy_env(const char **env);
char			*ft_getenv(char **env, char *elem);
int				len_env(char **env);
int				ft_echo(char **args);
int				builtin(char *arg);
int				exec_builtin(char **args, char ***env, char *line);
int				ft_cd(char **args, char ***env);
int				ft_env(char **args, const char **env, char *line);
void			ft_exit(char **args, char **env, char *line);
char			**ft_setenv(char **args, char **env);
char			**ft_unsetenv(char **args, char **env);
int				add_path(char **args, char **env);
char			**ft_replace(char **args, char **env);
int				ft_launch(char **args, char ***env, char *line);
void			enable_signal(void);
void			disable_signal(void);
void			ignore_signal(void);
void			check_segfault(char *prog, int status);
char			file_type(char *path);
char			*ft_join_path(char *path, char *link);
char			*fill_line(void);
int				is_a_special_key(char *buf);
void			apply_key(char *buf, t_cmdline *res);
void			ft_addchar(t_cmdline *res, char *buf);
int				ft_printchar(int c);
void			ft_leftkey(t_cmdline *res);
void			ft_rightkey(t_cmdline *res);
void			ft_tab(t_cmdline *res);
void			ft_backspace(t_cmdline *res);
int				ft_comp(char *word, char *name);
char			*find_path(char *word);
void			display_list(t_list *list);

#endif
