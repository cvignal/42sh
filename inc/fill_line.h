/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:40:31 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/08 15:12:24 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILL_LINE_H
# define FILL_LINE_H

# include "libft.h"
# include "shell.h"

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
# define CTRL_C "\x3\0\0\0\0\0"
# define CTRL_L "\xc\0\0\0\0\0"
# define CTRL_R "\x12\0\0\0\0\0"
# define RETURN "\n"
# define BACKSPACE "\b"
# define DEL_KEY "\033[3~"
# define CURS_POS "\033[6n"
# define F1_KEY "\033OP"
# define F2_KEY "\033OQ"
# define MAJ_DOWN "\033[1;2B"
# define MAJ_UP "\033[1;2A"
# define MAJ_RIGHT "\033[1;2C"
# define MAJ_LEFT "\033[1;2D"
# define F3_KEY "\033OR"
# define F4_KEY "\033OS"
# define F5_KEY "\033[15~"
# define MAJ_TAB "\033[Z"
# define ESCAPE "\033"
# define EOC "\e[0m"
# define HIST_SIZE_MAX 50000
# define NOT_A_TTY "Line edition disabled\n$> "

typedef struct	s_key
{
	char	*value;
	int		(*f)(t_shell *shell);
}				t_key;

typedef struct	s_curs
{
	int	col;
	int	line;
}				t_curs;

extern int		g_fd_output;

/*
** Initialization and read
*/
int				fill_line(t_shell *shell);
int				is_a_special_key(char *buf);
int				apply_key(char *buf, t_shell *shell);
void			ft_addchar(t_shell *shell, char *buf);
int				ft_printchar(int c);
void			reset_terminal_mode(t_shell *shell);
void			raw_terminal_mode(t_shell *shell);
int				check_validity(t_shell *shell);

/*
** Special keys
*/
int				ft_ctrlc(t_shell *shell);
int				ft_leftkey(t_shell *shell);
int				ft_homekey(t_shell *shell);
int				ft_endkey(t_shell *shell);
int				ft_rightkey(t_shell *shell);
int				ft_tab(t_shell *shell);
int				ft_backspace(t_shell *shell);
int				ft_nextword(t_shell *shell);
int				ft_prevword(t_shell *shell);
int				ft_lineup(t_shell *shell);
int				ft_linedown(t_shell *shell);
int				ft_ctrld(t_shell *shell);
int				ft_switch_mode(t_shell *shell);
int				ft_copy(t_shell *shell);
int				ft_paste(t_shell *shell);
int				ft_cut(t_shell *shell);
int				ft_hisdown(t_shell *shell);
int				ft_hisup(t_shell *shell);
int				ft_ctrll(t_shell *shell);
int				ft_ctrlr(t_shell *shell);

/*
** Tools for autocompletion
*/
int				ft_comp(char *word, char *name);
char			*find_path(char *word);
void			display_list(t_list *list);
void			clean_under_line(t_shell *shell);
char			*word_to_complete(t_line *line);
void			ft_add_builtins(char *word, t_list **list);

/*
** Tools for multi lines and cursor motion
*/
int				nb_multi_lines(size_t len);
void			clear_cmd_line(t_shell *shell);
t_curs			*get_cursor_pos(void);
size_t			length_curr_line(t_shell *shell);
void			scroll_lines(t_shell *shell);
void			move_lines(t_shell *shell);

/*
** Tools for history
*/
int				add_to_history(char *str, t_shell *shell, int flag);
int				load_history(t_shell *shell);
size_t			length_prev_line(t_shell *shell);

#endif
