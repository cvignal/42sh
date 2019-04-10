/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <gchainet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 09:56:58 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 19:17:43 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "parser.h"
# include "ast.h"
# include "expr.h"
# include "libft.h"
# include "expand.h"

# define EXEC_NAME "42sh"
# define PROMPT "$>"
# define INCOMPLETE_INPUT_PROMPT ">"

# define SYNTAX_ERROR_MSG "syntax error"
# define MEMORY_ERROR_MSG "unable to allocate memory"
# define COMMAND_NOT_FOUND_MSG "command not found"
# define ERR_CHAR_VAR "invalid characters in var name"
# define ERR_LEN_VAR "variable too long"
# define FC_0 "fc: usage:\n"
# define FC_1 "\t(i)   fc [-r] [-e editor] [[first] [last]]\n"
# define FC_2 "\t(ii)  fc -l [-nr] [first [last]]\n"
# define FC_3 "\t(iii) fc -s [pat=rep] [command]"
# define FC_USAGE_MESSAGE FC_0 FC_1 FC_2 FC_3

# define ARGS_ALLOC_SIZE 8
# define HEREDOC_ALLOC_SIZE 256
# define LINE_ALLOC_SIZE 128
# define HASH_TABLE_SIZE (1 << 16)

# define CHAR_TILDE	'~'
# define CHAR_VAR '$'

# define MAX_PATH	1024
# define VAR_MAX 1024
# define SEARCH_MAX 128

typedef struct		s_curs
{
	int	col;
	int	line;
}					t_curs;

typedef struct		s_hbt
{
	char			*bin;
	char			*path;
	struct s_hbt	*left;
	struct s_hbt	*right;
}					t_hbt;

typedef struct		s_line
{
	char			*data;
	char			search[SEARCH_MAX];
	size_t			len_search;
	size_t			curs_search;
	size_t			alloc_size;
	size_t			len;
	unsigned int	cursor;
	unsigned int	select_curs;
}					t_line;

typedef struct		s_fd
{
	int				fd;
	int				is_pipe;
	struct s_fd		*next;
}					t_fd;

typedef struct		s_shell
{
	t_lexer			lexer;
	t_parser		parser;
	t_exp_lexer		exp_lexer;
	char			**env;
	t_line			line;
	t_array			*history;
	int				his_pos;
	t_hbt			**hash_table;
	char			*pbpaste;
	int				fd_op;
	t_fd			*used_fd;
	int				ctrld;
	int				ctrlc;
	int				end_heredoc;
	int				prev_cmd_state;
	int				ret_cmd;
	t_token			*output;
	t_token			*current;
	int				prompt_len;
	int				fc_cmd;
}					t_shell;

struct s_redir;
typedef int			(*t_redir_act)(t_shell *, t_ast *, struct s_redir *);
typedef int			(*t_redir_apply)(struct s_redir *);

int					reset_redirs(t_shell *shell, t_ast *instr);

typedef struct		s_redir
{
	t_ttype			type;
	char			*target;
	char			*target_value;
	int				in;
	int				out;
	int				fd;
	int				applied;
	t_redir_act		redir_act;
	struct s_redir	*next;
}					t_redir;

typedef struct		s_redir_desc
{
	int				type;
	t_redir_act		act;
}					t_redir_desc;

typedef struct		s_redir_apply_desc
{
	t_ttype			type;
	t_redir_apply	apply;
}					t_redir_apply_desc;

typedef struct		s_command
{
	char			**args;
	char			**args_value;
	size_t			alloc_size;
	size_t			args_len;
	pid_t			pid;
}					t_command;

typedef int			(*t_builtin)(t_shell *, char **);

typedef struct		s_builtin_desc
{
	char			*desc;
	t_builtin		builtin;
}					t_builtin_desc;

typedef struct		s_heredoc
{
	char			*data;
	size_t			alloc_size;
	size_t			len;
}					t_heredoc;

typedef struct		s_fc
{
	char			*first;
	char			*last;
	char			*editor;
	char			*old_p;
	char			*new_p;
	int				i_first;
	int				i_last;
	char			flags[4];
}					t_fc;

typedef struct		s_tmpfile
{
	char	*name;
	int		fd;
}					t_tmpfile;

t_heredoc			*alloc_heredoc(void);
int					add_to_heredoc(t_heredoc *heredoc, const char *line);
int					heredoc_exit_error(t_heredoc *heredoc);
int					read_heredoc(t_heredoc *heredoc, t_redir *redir);

/*
** command.c
*/
t_command			*alloc_command(void);
void				free_command(t_command *command);
int					add_to_command(t_command *command, char *word);

/*
** exec.c
*/
pid_t				exec(t_shell *shell, t_ast *instr);
int					exec_from_char(t_shell *shell, char **arg,
					t_shell *tmp_shell);
int					wait_loop(t_ast *ast);

/*
** path.c
*/
char				*find_command(t_shell *shell, const char *command);

/*
** shell.c
*/
int					free_shell(t_shell *shell);
int					init_shell(t_shell *shell, char **environ);

/*
** line.c
*/
int					add_to_line(t_line *line, char buf);
int					free_line(t_line *line);

/*
** env.c
*/
int					set_env_var(t_shell *shell, const char *var,
					const char *value);
void				remove_env(t_shell *shell);

/*
** env_utils.c
*/
char				**copy_env(char **env);
char				**split_env_arg(char *arg);
char				*get_env_value(t_shell *shell, char *name);
int					remove_env_value(t_shell *shell, char *name);

/*
** builtins/
*/
t_builtin			is_builtin(char *cmd);
int					builtin_cd(t_shell *shell, char **args);
int					builtin_env(t_shell *shell, char **args);
int					builtin_env_get_opts(char **args, t_shell *tmp_shell);
int					builtin_setenv(t_shell *shell, char **args);
int					builtin_unsetenv(t_shell *shell, char **args);
int					builtin_echo(t_shell *shell, char **args);
int					builtin_exit(t_shell *shell, char **args);
int					exec_builtin(t_shell *shell, t_builtin builtin,
		t_ast *instr);
int					builtin_type(t_shell *shell, char **args);
void				print_only_type(char **args, int i, char *flags
		, t_shell *shell);
void				print_loc_type(char **args, int i, char *flags
		, t_shell *shell);
int					builtin_hash(t_shell *shell, char **args);
int					builtin_test(t_shell *shell, char **args);
void				print_rec_tree(t_hbt *node);

/*
** fc
*/
int					builtin_fc(t_shell *shell, char **args);
int					usage_fc(void);
int					fc_init_args(t_fc *cmd, char **args, t_shell *shell);
void				fc_index(t_fc *cmd, t_shell *shell);
void				free_fc(t_fc *cmd);
int					fc_cut_pattern(t_fc *cmd, char *str);
int					fc_open_file(t_fc *cmd, t_shell *shell, t_tmpfile *file);
int					fc_open_editor(t_fc *cmd, t_tmpfile *file, t_shell *shell);
int					fc_exec_line(char *str, t_shell *shell);
int					fc_exec_file(char *name, t_shell *shell);
void				fc_exec_ast(t_shell *shell, t_token *tokens);
void				fc_free_shell(t_shell *shell);
int					fc_init_shell(t_shell *shell, t_shell *old_shell);
int					fc_find_cmd(char *str, t_array *history);

/*
** signal.c
*/
t_shell				*save_shell(t_shell *shell);

/*
** exec
*/
struct s_ast;
int					exec_cmd(t_shell *shell, struct s_ast *ast);
void				free_cmd(struct s_ast *ast);
int					exec_pipeline(t_shell *shell, struct s_ast *ast);
void				free_pipeline(struct s_ast *ast);
int					exec_end(t_shell *shell, struct s_ast *ast);
void				free_end(struct s_ast *ast);
int					exec_cmd(t_shell *shell, struct s_ast *ast);
void				free_cmd(struct s_ast *ast);
int					exec_end(t_shell *shell, struct s_ast *ast);
void				free_end(struct s_ast *ast);
int					exec_or(t_shell *shell, struct s_ast *ast);
void				free_or(struct s_ast *ast);
int					exec_and(t_shell *shell, struct s_ast *ast);
void				free_and(struct s_ast *ast);
int					exec_expr(t_shell *shell, struct s_ast *ast);
void				free_expr(struct s_ast *ast);
int					exec_if(t_shell *shell, struct s_ast *ast);
void				free_if(struct s_ast *ast);
int					exec_else(t_shell *shell, struct s_ast *ast);
void				free_else(struct s_ast *ast);
int					exec_while(t_shell *shell, struct s_ast *ast);
void				free_while(struct s_ast *ast);

/*
** redir.c
*/
t_redir				*create_redir(t_ttype type, char *arg, t_redir_act act);
void				add_to_redir_list(t_ast *instr, t_redir *redir);

/*
** redir_internal.c
*/
int					prepare_redirs(t_shell *shell, t_ast *instr, t_ast *root);
int					redir_l(t_shell *shell, t_ast *ast, t_redir *redir);
int					redir_ll(t_shell *shell, t_ast *ast, t_redir *redir);
int					redir_r(t_shell *shell, t_ast *ast, t_redir *redir);
int					redir_rr(t_shell *shell, t_ast *ast, t_redir *redir);
int					expand_heredoc(t_heredoc *heredoc, t_shell *shell
		, int fd[2]);

/*
** apply_redirs.c
*/
int					apply_redirs(t_shell *shell, t_ast *instr);
int					apply_redir_generic(t_redir *redir);
int					apply_redir_r_close(t_redir *redir);
int					apply_redir_r_both(t_redir *redir);
int					apply_redir_r_comp(t_redir *redir);
int					apply_redir_rw(t_redir *redir);

/*
** redir_r_comp.c
*/
int					redir_r_comp(t_shell *shell, t_ast *ast, t_redir *redir);

/*
** redir_r_close.c
*/
int					redir_r_close(t_shell *shell, t_ast *ast, t_redir *redir);

/*
** redir_r_both.c
*/
int					redir_r_both(t_shell *shell, t_ast *ast, t_redir *redir);

/*
** redir_rw.c
*/
int					redir_rw(t_shell *shell, t_ast *ast, t_redir *redir);

/*
** pipeline.c
*/
int					set_pipeline(t_shell *shell, t_ast *instr);
int					open_pipe(t_shell *shell, int *fd);

/*
** propagate_pipe.c
*/
int					propagate_pipe_left(t_ast *pipe, t_ast *instr);

/*
** hash.c
*/
char				*hbt_command(t_shell *shell, const char *elem);
void				free_hbt(t_hbt *hbt);
void				sanitize_hash(t_shell *shell);

/*
** signal.c
*/
void				prompt_signal_handler(int sig);
void				disable_signal(t_shell *shell);
void				enable_signal(void);

/*
** fd.c
*/
int					get_next_fd(t_shell *shell);
int					add_fd(t_shell *shell, int fd, int is_pipe);
int					open_file(t_shell *shell, const char *file, int mode,
		int perm);
void				remove_fd(t_shell *shell, int fd);
void				close_everything(t_shell *shell);

/*
** tools_fd.c
*/
void				add_tty_history_fd(t_shell *shell, t_fd *tty_fd
		, t_fd *hf_fd);

/*
** alt_shell.c
*/
int					alt_init_shell(t_shell *shell);

#endif
