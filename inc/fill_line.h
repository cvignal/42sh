/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:40:31 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/26 19:01:36 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILL_LINE_H
# define FILL_LINE_H

# include "libft.h"
# include "21sh.h"

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
# define CURS_POS "\033[6n"
# define F1_KEY "\033OP"
# define F2_KEY "\033OQ"
# define MAJ_DOWN "\033[1;2B"
# define MAJ_UP "\033[1;2A"
typedef struct	s_key
{
	char	*value;
	void	(*f)(t_shell *shell);
}				t_key;

typedef struct	s_curs
{
	int	col;
	int	line;
}				t_curs;

int				fill_line(t_shell *shell);
int				is_a_special_key(char *buf);
void			apply_key(char *buf, t_shell *shell);
void			ft_addchar(t_shell *shell, char *buf);
int				ft_printchar(int c);
void			ft_leftkey(t_shell *shell);
void			ft_homekey(t_shell *shell);
void			ft_endkey(t_shell *shell);
void			ft_rightkey(t_shell *shell);
void			ft_tab(t_shell *shell);
void			ft_backspace(t_shell *shell);
void			ft_nextword(t_shell *shell);
void			ft_prevword(t_shell *shell);
void			ft_lineup(t_shell *shell);
void			ft_linedown(t_shell *shell);
int				ft_comp(char *word, char *name);
char			*find_path(char *word);
void			display_list(t_list *list);
void			clean_under_line(void);
void			ft_hisdown(t_shell *shell);
void			ft_hisup(t_shell *shell);
t_curs			*get_cursor_pos(void);
void			reset_terminal_mode(void);
void			raw_terminal_mode(void);
char			*word_to_complete(char *line);

#endif
