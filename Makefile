# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvignal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/07 16:39:44 by cvignal           #+#    #+#              #
#    Updated: 2019/06/26 08:11:51 by marin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############################
#         VARIABLES         #
#############################
#### FILE STRUCTURE ####
NAME	:=	42sh

SRC	=	alt_shell.c apply_redir_rw.c apply_redirs.c arg_file.c		\
		command.c env.c	exec.c	main.c	fd.c hash.c hash_sanitize.c	\
		heredoc.c path.c pipeline.c prompt.c propagate_pipe.c redir.c	\
		redir_close.c redir_internal.c redir_l_comp.c redir_r_both.c	\
		redir_r_comp.c redir_reset.c redir_rw.c shell.c signal.c	\
		tools_fd.c tools_heredoc.c utils.c wait.c			\

SRC	+=	$(addprefix builtins/, 					\
		builtin_hash.c builtins.c cd.c echo.c exec_builtin.c	\
		exit.c	fc.c fc_display.c fc_exec.c file_fc.c idx_fc.c  \
		jobs.c parsing_fc.c setenv.c tools_cd.c	tools_fc.c	\
		tools_hash.c tools_type.c trim_path.c type.c unset.c	\
		unsetenv.c					        \
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
		special_params_expansion_2.c						\
		)

SRC	+=	$(addprefix expr/,						\
		a.c b.c c.c d.c desc.c e.c ef.c eq.c equal.c			\
		expression.c f.c g.c g_cap.c ge.c gt.c h.c k.c			\
		l_cap.c le.c lower.c lt.c n.c n_cap.c ne.c not_equal.c		\
		nt.c o_cap.c ot.c p.c r.c s.c s_cap.c sup.c t.c			\
		u.c v.c w.c x.c
		)

SRC	+=	$(addprefix history_research/,				\
		algo_search.c ctrl_keys.c init_search.c move_keys.c	\
		other_movekeys.c tools_hs.c				\
		)
SRC	+=	$(addprefix jobs/,i					\
		job_print.c job_string.c job_state.c job_wait.c		\
		jobs.c utils.c						\
		)
	line_edition/autocompletion.c
	line_edition/backspace.c
	line_edition/cursor.c
	line_edition/delete.c
	line_edition/display_auto.c
	line_edition/fill_line.c
	line_edition/fn_keys.c
	line_edition/history.c
	line_edition/history_file.c
	line_edition/leftkey.c
	line_edition/line.c
	line_edition/line_keys.c
	line_edition/other_keys.c
	line_edition/parsing_auto.c
	line_edition/rightkey.c
	line_edition/switch_mode.c
	line_edition/term_mode.c
	line_edition/tools_auto.c
	line_edition/tools_history.c
	line_edition/tools_insertion.c
	line_edition/tools_keys.c
	line_edition/tools_motion.c
	line_edition/tools_path.c
	parser/arithmetic/init.c
	parser/arithmetic/lexer_actions.c
	parser/arithmetic/lexer_actions_paren.c
	parser/arithmetic/set_unary.c
	parser/arithmetic/type.c
	parser/assignement.c
	parser/ast.c
	parser/ast_token.c
	parser/free_token.c
	parser/init_lexer.c
	parser/init_parser.c
	parser/input_queue.c
	parser/keyword.c
	parser/lexer.c
	parser/lexer_act.c
	parser/lexer_act_escaped.c
	parser/lexer_act_meta.c
      	parser/lexer_act_meta2.c
	parser/lexer_act_over.c
	parser/lexer_act_quote.c
	parser/lss.c
	parser/op_prop.c
	parser/parser.c
	parser/parser_rules.c
	parser/pss.c
	parser/rules.c
	parser/rules_ari.c
	parser/rules_ari_decrementation.c
	parser/rules_ari_incrementation.c
	parser/rules_ari_mangle.c
	parser/rules_ari_op.c
	parser/rules_ari_usub.c
	parser/rules_expr.c
	parser/rules_if.c
	parser/rules_if_nocd.c
	parser/rules_logic.c
	parser/rules_parenthesis.c
	parser/rules_pipe.c
	parser/rules_redir.c
	parser/rules_redir_close.c
	parser/rules_redir_l_comp.c
	parser/rules_redir_r_both.c
	parser/rules_redir_r_comp.c
	parser/rules_redir_read_write.c
	parser/rules_shift.c
	parser/rules_shunting_yard.c
	parser/rules_statement.c
	parser/rules_syntax_error.c
	parser/rules_while.c
	parser/shunting_yard.c
	parser/token.c
	parser/token_type.c
	parser/token_type_desc.c
	parser/tools_shunting_yard.c
	parser/utils.c
	vars/special_vars.c
	vars/var.c
	vars/var_create.c
	vars/var_utils.c
	visual_mode/visual_mode.c
	visual_mode/vm_copy.c
	visual_mode/vm_cut.c
	visual_mode/vm_leftkey.c
	visual_mode/vm_rightkey.c

SRCDIR	:=	src
OBJDIR	:=	obj
DEPDIR	:=	dep
INCDIR	:=	inc
LIBDIR	:=	lib

## *LOCA is the list of all subdirectory in a directory
SRCLOCA	:=	$(shell find $(SRCDIR) -type d)
OBJLOCA	:=	$(subst $(SRCDIR), $(OBJDIR), $(SRCLOCA))
DEPLOCA	:=	$(subst $(SRCDIR), $(DEPDIR), $(SRCLOCA))

OBJ		:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEP		:=	$(addprefix $(DEPDIR)/, $(SRC:.c=.d))
SRC		:=	$(addprefix $(SRCDIR)/, $(SRC))

#### LIBRARY ####
# Libft
LIBFT_PATH	:= $(LIBDIR)/libft
include $(LIBFT_PATH)/include.mk

#### COMPILER ####
CC		?=	cc

INCFLAG	:= -I $(INCDIR) $(LIB_INC)
WFLAGS	?=	-Wall -Wextra -Werror -g
CFLAGS	=	$(WFLAGS) $(INCFLAG) $(STDFLAG)

DEPGEN	:=	$(CC)
DEPFLAG	:=	-MM $(INCFLAG)

LD		:=	$(CC)
LDFLAG	:=	$(LIB_LINK) -ltermcap

# Fill the variable if the command exist, note &> does not work
CLANG_INSTALLED	:= $(shell which clang > /dev/null 2> /dev/null && echo yes)


# Program linkage
$(NAME):	$(OBJ) | $(LIBFT_PATH)/$(LIBFT)

$(OBJDIR)/%.o:		$(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)

# Lib Compilation
$(LIBFT_PATH)/$(LIBFT):
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"	: "$@$(MOVELINE)
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory > $(TMP) 2> $(TMP) &&
		(echo $(CLEARLINE)$(CYAN)[OK]$(COLRESET)"	: "$@ ; rm $(TMP)) || \
		(echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"	: "$@ ; \
			cat $(TMP) | sed -e "s/^/    /g" ; rm $(TMP) ; exit 1)

