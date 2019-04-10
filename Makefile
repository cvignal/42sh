# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvignal <cvignal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/07 16:39:44 by cvignal           #+#    #+#              #
#    Updated: 2019/04/10 19:17:44 by fstadelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############################
#         VARIABLES         #
#############################
#### FILE STRUCTURE ####
NAME	:=	42sh

SRC		=								\
	main.c								\
	prompt.c							\
	alt_shell.c							\
	parser/token.c						\
	parser/free_token.c					\
	parser/token_type.c					\
	parser/token_type_desc.c			\
	parser/parser.c						\
	parser/input_queue.c				\
	parser/lexer_act.c					\
	parser/lexer_act_meta.c				\
	parser/lexer_act_quote.c			\
	parser/lexer_act_over.c				\
	parser/lss.c						\
	parser/pss.c						\
	parser/init_lexer.c					\
	parser/init_parser.c				\
	parser/lexer.c						\
	parser/parser_rules.c				\
	parser/keyword.c					\
	parser/rules.c						\
	parser/rules_expr.c					\
	parser/rules_shift.c				\
	parser/rules_logic.c				\
	parser/rules_redir.c				\
	parser/rules_redir_r_comp.c			\
	parser/rules_redir_r_close.c		\
	parser/rules_redir_r_both.c			\
	parser/rules_redir_read_write.c		\
	parser/rules_pipe.c					\
	parser/rules_statement.c			\
	parser/rules_if.c					\
	parser/rules_if_nocd.c				\
	parser/rules_while.c				\
	parser/rules_shunting_yard.c		\
	parser/shunting_yard.c				\
	parser/ast.c						\
	parser/ast_token.c					\
	parser/utils.c						\
	line_edition/line.c					\
	line_edition/fill_line.c			\
	line_edition/leftkey.c				\
	line_edition/rightkey.c				\
	line_edition/backspace.c			\
	line_edition/other_keys.c			\
	line_edition/tools_keys.c			\
	line_edition/tools_auto.c			\
	line_edition/tools_motion.c			\
	line_edition/tools_history.c		\
	line_edition/history_file.c			\
	line_edition/autocompletion.c		\
	line_edition/display_auto.c			\
	line_edition/history.c				\
	line_edition/cursor.c				\
	line_edition/fn_keys.c				\
	line_edition/line_keys.c			\
	line_edition/tools_insertion.c		\
	line_edition/delete.c				\
	line_edition/switch_mode.c			\
	history_research/init_search.c		\
	history_research/move_keys.c		\
	history_research/other_movekeys.c	\
	history_research/ctrl_keys.c		\
	history_research/algo_search.c		\
	history_research/tools_hs.c			\
	visual_mode/visual_mode.c			\
	visual_mode/vm_rightkey.c			\
	visual_mode/vm_leftkey.c			\
	visual_mode/vm_cut.c				\
	visual_mode/vm_copy.c				\
	exec/cmd.c							\
	exec/pipeline.c						\
	exec/end.c							\
	exec/or.c							\
	exec/and.c							\
	exec/expr.c							\
	exec/if.c							\
	exec/else.c							\
	exec/while.c						\
	shell.c								\
	command.c							\
	exec.c								\
	path.c								\
	env.c								\
	env_utils.c							\
	hash.c								\
	hash_sanitize.c						\
	heredoc.c							\
	propagate_pipe.c					\
	redir.c								\
	redir_reset.c						\
	apply_redirs.c						\
	apply_redir_rw.c					\
	redir_r_comp.c						\
	redir_r_close.c						\
	redir_r_both.c						\
	redir_rw.c							\
	redir_internal.c					\
	tools_heredoc.c						\
	pipeline.c							\
	builtins/builtins.c					\
	builtins/exec_builtin.c				\
	builtins/cd.c						\
	builtins/echo.c						\
	builtins/env.c						\
	builtins/env_options.c				\
	builtins/setenv.c					\
	builtins/unsetenv.c					\
	builtins/exit.c						\
	builtins/type.c						\
	builtins/test.c						\
	builtins/tools_type.c				\
	builtins/builtin_hash.c				\
	builtins/tools_hash.c				\
	builtins/fc.c						\
	builtins/parsing_fc.c				\
	builtins/tools_fc.c					\
	builtins/idx_fc.c					\
	builtins/file_fc.c					\
	builtins/fc_exec.c					\
	expr/expression.c					\
	expr/desc.c							\
	expr/a.c							\
	expr/b.c							\
	expr/c.c							\
	expr/d.c							\
	expr/e.c							\
	expr/f.c							\
	expr/g.c							\
	expr/h.c							\
	expr/k.c							\
	expr/p.c							\
	expr/r.c							\
	expr/s.c							\
	expr/t.c							\
	expr/u.c							\
	expr/w.c							\
	expr/x.c							\
	expr/g_cap.c						\
	expr/l_cap.c						\
	expr/n_cap.c						\
	expr/o_cap.c						\
	expr/s_cap.c						\
	expr/ef.c							\
	expr/nt.c							\
	expr/ot.c							\
	expr/v.c							\
	expr/n.c							\
	expr/equal.c						\
	expr/not_equal.c					\
	expr/lower.c						\
	expr/sup.c							\
	expr/eq.c							\
	expr/ne.c							\
	expr/lt.c							\
	expr/le.c							\
	expr/gt.c							\
	expr/ge.c							\
	signal.c							\
	tools_fd.c							\
	fd.c								\
	wait.c								\
	expansion/buffer.c					\
	expansion/exp_ss.c					\
	expansion/init.c					\
	expansion/lexer.c					\
	expansion/lexer_methods.c			\
	expansion/lexer_methods_quotes.c	\
	expansion/lexer_methods_hist.c		\
	expansion/home.c					\
	expansion/expr.c

SRCDIR	:=	src
OBJDIR	:=	obj
DEPDIR	:=	dep
INCDIR	:=	inc
LIBDIR	:=	lib

# File used as a command output buffer
TMP		:=	.tmp.txt

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
WFLAGS	?=	-Wall -Wextra -Werror
CFLAGS	=	$(WFLAGS) $(INCFLAG) $(STDFLAG)

DEPGEN	:=	$(CC)
DEPFLAG	:=	-MM $(INCFLAG)

LD		:=	$(CC)
LDFLAG	:=	$(LIB_LINK) -ltermcap

# Fill the variable if the command exist, note &> does not work
CLANG_INSTALLED	:= $(shell which clang > /dev/null 2> /dev/null && echo yes)

#############################
#          COLORS           #
#############################
ifdef TERM
RED			:=	"\033[1;31m"
GREEN		:=	"\033[0;32m"
BGREEN		:=	"\033[1;32m"
BLUE		:=	"\033[0;34m"
YELLOW		:=	"\033[0;33m"
PURPLE		:=	"\033[0;35m"
CYAN		:=	"\033[0;36m"
GREY		:=	"\033[0;37m"
# When printed reset the color
COLRESET	:=	"\033[0m"
endif

COMPCOLOR	:=	$(GREEN)
LINKCOLOR	:=	$(PURPLE)
ONGOINGCOL	:=	$(YELLOW)
KOCOLOR		:=	$(RED)
RMCOLOR		:=	$(GREY)

MOVELINE	:=	"\033[1A"
CLEARLINE	:=	"\033[K"

#############################
#           RULES           #
#############################
#### COMPILE ####
# Standard rule used when just calling $> make
all:		$(NAME)

# Program linkage
$(NAME):	$(OBJ) | $(LIBFT_PATH)/$(LIBFT)
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"	: "$@$(MOVELINE)
	@ $(LD) -o $(NAME) $(OBJ) $(LDFLAG) &> $(TMP) && \
		(echo $(CLEARLINE)$(LINKCOLOR)[shell]$(COLRESET)"	: created"  ; \
			cat $(TMP) | sed -e "s/^/    /g" ; rm $(TMP)) || \
		(echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"	: linkage fail" ; \
			cat $(TMP) | sed -e "s/^/    /g" ; rm $(TMP) ; exit 1)

# Compilation and .d generation
$(OBJDIR)/%.o:		$(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"	: "$@$(MOVELINE)
	@ $(CC) -c $< $(CFLAGS) -o  $@ &> $(TMP) && \
		(echo $(CLEARLINE)$(COMPCOLOR)[OK]$(COLRESET)"	: "$@ ; \
			cat $(TMP) | sed -e "s/^/    /g") || \
		(echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"	: "$@ ; \
			cat $(TMP) | sed -e "s/^/    /g" ; rm $(TMP) ; exit 1)
	@ $(DEPGEN) -c $< $(DEPFLAG) -MQ $@ \
		> $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

# Lib Compilation
$(LIBFT_PATH)/$(LIBFT):
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"	: "$@$(MOVELINE)
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory > $(TMP) 2> $(TMP) && \
		(echo $(CLEARLINE)$(CYAN)[OK]$(COLRESET)"	: "$@ ; rm $(TMP)) || \
		(echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"	: "$@ ; \
			cat $(TMP) | sed -e "s/^/    /g" ; rm $(TMP) ; exit 1)

# Dir created to store .d and .o
$(OBJDIR):
	@ mkdir -p $(OBJLOCA)
$(DEPDIR):
	@ mkdir -p $(DEPLOCA)

# Recompile with as much warning as possible
warn:	WFLAGS := -Wall -Wextra -ansi -Wpedantic -Wno-vla
# If clang is installed also add this exclusive warning
ifdef CLANG_INSTALLED
warn:	CC := clang
warn:	WFLAGS += -Weverything
endif
warn:	lre

#### FORBIDEN FUNCTION ####
# Check forbiden funcion call
# All functions listed in .function_whitelist.txt are authorised
ffcheck:	$(NAME)
	@ nm -u $(NAME) | \
		sed -e 's/^\s*U\s//g' | grep -Ev '^\s*w\s|^__|dyld_stub_binder' | \
		grep -Ev \
			`cat .function_whitelist.txt | \
			sed -e 's/^/\^_?/g' | sed -e 's/$$/|/g' | \
			tr -d '\n' | sed 's/|$$//g'` &> $(TMP) ; \
		wc -l < $(TMP) | grep -e '^\s*\0$$' &> /dev/null && \
	echo $(BGREEN)[func]$(COLRESET)"	: no forbiden functions found" || \
	(echo $(RED)[func]$(COLRESET)"	: forbiden functions found" ; \
		cat $(TMP) | sed -e "s/^/    /g" ; rm $(TMP))

#### NORM ####
norm:
	@ norminette $(SRC) $(INCDIR) | \
		(! grep -E -B 1 "(^Warning|^Error)" &> $(TMP)) && \
		echo $(CYAN)[NORM]$(COLRESET)"	: pass, it's ok for now" || \
		(echo $(RED)[NORM]$(COLRESET)"	: you failed miserably !" ; \
		cat $(TMP) | sed -e "s/^/    /g" ; rm $(TMP))

sure: warn ffcheck norm

#### DEBUGING ####
# Change warning flag to debug and local recompile
debug:	WFLAGS	:= -g3 -ggdb
debug:	all

rdebug:	WFLAGS	:= -g3 -ggdb
rdebug:	lre

fsan:	WFLAGS	:= -g -fsanitize=address
fsan:	LDFLAG	+= -fsanitize=address
fsan:	all

rfsan:	WFLAGS	:= -g -fsanitize=address
fsan:	LDFLAG	+= -fsanitize=address
rfsan:	lre

#### TESTS ####
# Use when you have some error and just want to rest
test:	WFLAGS :=
test:	all

# Test with everything recompile
rtest:	WFLAGS :=
rtest:	lre

#### LOCAL (Don't recompile lib) ####
lclean:
	@ rm -r $(OBJDIR) &> /dev/null && \
		echo $(RMCOLOR)[CLR]$(COLRESET)"	:" obj ; (exit 0)
	@ rm -r $(DEPDIR) &> /dev/null && \
		echo $(RMCOLOR)[CLR]$(COLRESET)"	:" dep ; (exit 0)
	@ rm -rfd 21sh.dSYM

lfclean: lclean
	@ rm $(NAME) &> /dev/null && \
		echo $(RMCOLOR)[CLR]$(COLRESET)"	:" $(NAME) ; (exit 0)

lre: lfclean all

#### MANDATORY ####
clean: lclean
	@ rm -f $(TMP)
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory clean

fclean:	lfclean
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory fclean

re:		fclean all

#############################
#          SETTING          #
#############################
# Add rule to phony if they are not based on actual files.
.PHONY: all clean fclean re
.PHONY: callg ffcheck norm sure
.PHONY: debug warn test rtest
.PHONY: lclean lfclean lre

#############################
#         DEPENDENCY        #
#############################
# Include all custom dependency rules created in .d's
# the '-' prevent error in case of non existing files
-include $(DEP)
