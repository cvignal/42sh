/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 09:56:58 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/12 02:31:00 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "parser.h"
# include "ast.h"
# include "expr.h"
# include "libft.h"
# include "expand.h"

# define EXEC_NAME "21sh"
# define PROMPT "$>"
# define INCOMPLETE_INPUT_PROMPT ">"

# define SYNTAX_ERROR_MSG "syntax error"
# define MEMORY_ERROR_MSG "unable to allocate memory"
# define COMMAND_NOT_FOUND_MSG "command not found"

# define ARGS_ALLOC_SIZE 8
# define HEREDOC_ALLOC_SIZE 256
# define LINE_ALLOC_SIZE 128
# define HASH_TABLE_SIZE (1 << 16)

# define CHAR_TILDE	'~'
# define CHAR_VAR '$'

# define MAX_PATH	1024

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
	size_t			alloc_size;
	size_t			len;
	unsigned int	cursor;
	unsigned int	select_curs;
	int				mode;
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
	t_list			*history;
	int				his_pos;
	t_hbt			**hash_table;
	char			*pbpaste;
	int				fd_hf;
	int				fd_op;
	t_fd			*used_fd;
	int				ctrld;
	int				end_heredoc;
	int				prev_cmd_state;
	t_token			*output;
	t_token			*current;
}					t_shell;

struct s_redir;
typedef int			(*t_redir_act)(t_shell *, t_ast *, struct s_redir *);
typedef int			(*t_redir_apply)(struct s_redir *);

int					reset_redirs(t_shell *shell, t_ast *instr);

typedef struct		s_redir
{
	t_ttype			type;
	char			*target;
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
void				free_shell(t_shell *shell);
int					init_shell(t_shell *shell, char **environ);

/*
** line.c
*/
int					add_to_line(t_line *line, char *s);
void				free_line(t_line *line);

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
** buiiltins/
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

/*
** signal.c
*/
void				signal_sigint(int sig);

/*
** exec*
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
void				sanitize_hash(t_shell *shell);

/*
** signal.c
*/
void				disable_signal(void);
void				enable_signal(void);
void				ignore_signal(void);

/*
** fd.c
*/
int					get_next_fd(t_shell *shell);
int					add_fd(t_shell *shell, int fd, int is_pipe);
int					open_file(t_shell *shell, const char *file, int mode,
		int perm);
void				remove_fd(t_shell *shell, int fd);
void				close_everything(t_shell *shell);

#endif
