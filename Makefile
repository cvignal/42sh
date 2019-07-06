# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvignal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/07 16:39:44 by cvignal           #+#    #+#              #
#    Updated: 2019/07/06 17:51:11 by cvignal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	alt_shell.c apply_redir_rw.c apply_redirs.c arg_file.c		\
		command.c env.c	exec.c	main.c	fd.c hash.c hash_sanitize.c	\
		heredoc.c path.c pipeline.c prompt.c propagate_pipe.c redir.c	\
		redir_close.c redir_internal.c redir_l_comp.c redir_r_both.c	\
		redir_r_comp.c redir_reset.c redir_rw.c shell.c signal.c	\
		tools_fd.c tools_heredoc.c utils.c wait.c			\

SRC	+=	$(addprefix builtins/, 					\
		builtin_hash.c builtins.c cd.c echo.c exec_builtin.c	\
		exit.c	fc.c fc_display.c fc_exec.c file_fc.c idx_fc.c  \
		jobs.c parsing_fc.c tools_cd.c	tools_fc.c	\
		tools_hash.c tools_type.c trim_path.c type.c unset.c	\
		set.c export.c export_set_utils.c test.c test_ops.c	\
		)
SRC	+=	$(addprefix exec/,					\
		and.c async.c cmd.c else.c end.c expr.c if.c	or.c 	\
		pipeline.c while.c					\
		$(addprefix arithmetic/,					\
			and.c cmp_eq.c cmp_inf.c cmp_inf_eq.c cmp_not_eq.c cmp_sup.c		\
			cmp_sup_eq.c del.c div.c eq.c fail.c mod.c or.c plus.c plus_plus.c 	\
			prod.c statement.c sub.c sub_sub.c usub.c utils.c value.c		\
			)							\
		)

SRC	+=	$(addprefix expansion/,							\
		buffer.c exp_ss.c special_param_join_args.c expr.c			\
		parsing_hist.c home.c exp_hist.c init.c lexer.c				\
		lexer_methods.c lexer_methods_ari.c lexer_methods_special_params.c	\
		lexer_methods_dollar.c lexer_methods_escaped.c special_params.c		\
		lexer_methods_over.c lexer_methods_proc_sub.c lexer_methods_quotes.c	\
		lexer_methods_curly_exp.c special_params_expansion_1.c			\
		special_params_expansion_2.c utils_lexer.c						\
		)

SRC	+=	$(addprefix expr/,						\
		a.c b.c c.c d.c desc.c e.c ef.c eq.c equal.c			\
		expression.c f.c g.c g_cap.c ge.c gt.c h.c k.c			\
		l_cap.c le.c lower.c lt.c n.c n_cap.c ne.c not_equal.c		\
		nt.c o_cap.c ot.c p.c r.c s.c s_cap.c sup.c t.c			\
		u.c v.c w.c x.c							\
		)

SRC	+=	$(addprefix history_research/,				\
		algo_search.c ctrl_keys.c init_search.c move_keys.c	\
		other_movekeys.c tools_hs.c				\
		)
SRC	+=	$(addprefix jobs/,					\
		job_print.c job_string.c job_state.c job_wait.c		\
		jobs.c utils.c						\
		)
SRC	+=	$(addprefix line_edition/,					\
		autocompletion.c backspace.c cursor.c delete.c display_auto.c	\
		fill_line.c fn_keys.c history.c history_file.c leftkey.c	\
		line.c line_keys.c other_keys.c parsing_auto.c rightkey.c	\
		switch_mode.c term_mode.c tools_auto.c tools_history.c		\
		tools_insertion.c tools_keys.c tools_motion.c tools_path.c	\
		)
SRC	+=	$(addprefix parser/,								\
		ast.c ast_token.c free_token.c init_lexer.c init_parser.c				\
		input_queue.c keyword.c lexer.c lexer_act.c lexer_act_escaped.c				\
		lexer_act_meta.c lexer_act_meta2.c lexer_act_over.c lexer_act_quote.c			\
		lss.c op_prop.c parser.c parser_rules.c pss.c rules.c rules_ari.c			\
		rules_ari_decrementation.c rules_ari_incrementation.c rules_ari_mangle.c		\
		rules_ari_op.c rules_ari_usub.c rules_expr.c rules_if.c rules_if_nocd.c			\
		rules_logic.c rules_parenthesis.c rules_pipe.c rules_redir.c rules_redir_close.c	\
		rules_redir_l_comp.c rules_redir_r_both.c rules_redir_r_comp.c				\
		rules_redir_read_write.c rules_shift.c rules_shunting_yard.c rules_statement.c		\
		rules_syntax_error.c rules_while.c shunting_yard.c token.c token_type.c			\
		token_type_desc.c tools_shunting_yard.c utils.c assignement.c				\
		$(addprefix arithmetic/,								\
			init.c lexer_actions.c lexer_actions_paren.c set_unary.c			\
			type.c										\
		)											\
		)

SRC	+=	$(addprefix vars/,			\
		special_vars.c var.c var_create.c var_utils.c	\
		)
	
SRC	+=	$(addprefix visual_mode/,			\
		visual_mode.c vm_copy.c vm_cut.c vm_leftkey.c	\
		vm_rightkey.c					\
		)

NAME		:=	42sh

LIBFTDIR	:=	lib/libft
SRCDIR		:=	src
INCDIR		:=	inc
OBJDIR		:=	obj
DEPDIR		:=	dep

CC		:=	cc
LD		:=	cc
DEPGEN	:=	cc
RM		:=	rm -rf

CFLAGS		:=	-Wall -Werror -Wextra -g3
LDFLAGS		:=	-L $(LIBFTDIR) -lft -ltermcap
IFLAGS		:=	-I $(INCDIR) -I $(LIBFTDIR)/$(INCDIR)
DFLAGS		:=	-MM $(IFLAGS)

OBJ			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEP			:=	$(addprefix $(DEPDIR)/, $(SRC:.c=.d))
SRC			:=	$(addprefix $(SRCDIR)/, $(SRC))

SUBDIRS		:=	$(dir $(DEP)) $(dir $(OBJ))

$(NAME):	 make_dirs $(OBJ)
	make -C $(LIBFTDIR)
	$(LD) -o $(NAME) $(OBJ) $(LDFLAGS) 

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	$(DEPGEN) $(DFLAGS) -c $< -MQ $@ > $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

make_dirs:
	@mkdir -p $(SUBDIRS)

debug:
	$(CFLAGS += -ggdb)
	make all

all:		$(NAME)

clean:
	$(RM) $(OBJDIR)
	$(RM) $(DEPDIR)

fclean:		clean
	$(RM) $(NAME)

re:			fclean 
	make $(NAME)

-include $(DEP)

.PHONY:	clean fclean re
