# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvignal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/20 14:14:18 by cvignal           #+#    #+#              #
#    Updated: 2019/01/22 11:35:03 by cvignal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############################
#         VARIABLES         #
#############################
#### FILE STRUCTURE ####
NAME    :=      libft.a

SRC			= ft_memset.c			\
			  ft_bzero.c			\
			  ft_memcpy.c			\
			  ft_memccpy.c			\
			  ft_memmove.c			\
			  ft_memchr.c			\
			  ft_memcmp.c			\
			  ft_strlen.c			\
			  ft_strdup.c			\
			  ft_strcpy.c			\
			  ft_strncpy.c			\
			  ft_strcat.c			\
			  ft_strncat.c			\
			  ft_strlcat.c			\
			  ft_strchr.c			\
			  ft_strrchr.c			\
			  ft_strstr.c			\
			  ft_strnstr.c			\
			  ft_strcmp.c			\
			  ft_strncmp.c			\
			  ft_atoi.c				\
			  ft_isalpha.c			\
			  ft_isdigit.c			\
			  ft_isalnum.c			\
			  ft_isascii.c			\
			  ft_isprint.c			\
			  ft_toupper.c			\
			  ft_tolower.c			\
			  ft_memalloc.c			\
			  ft_memdel.c			\
			  ft_strnew.c			\
			  ft_strdel.c			\
			  ft_strclr.c			\
			  ft_striter.c			\
			  ft_memalloc.c			\
			  ft_striteri.c			\
			  ft_strmap.c			\
			  ft_strmapi.c			\
			  ft_strequ.c			\
			  ft_strnequ.c			\
			  ft_strsub.c			\
			  ft_strjoin.c			\
			  ft_strtrim.c			\
			  ft_strsplit.c			\
			  ft_putstr.c			\
			  ft_putchar.c			\
			  ft_putendl.c			\
			  ft_putnbr.c			\
			  ft_putchar_fd.c		\
			  ft_putstr_fd.c		\
			  ft_putendl_fd.c		\
			  ft_putnbr_fd.c		\
			  ft_lstnew.c			\
			  ft_lstdelone.c		\
			  ft_lstdel.c			\
			  ft_lstadd.c			\
			  ft_lstiter.c			\
			  ft_lstmap.c			\
			  ft_lstapp.c			\
			  ft_strsplit_lst.c		\
			  ft_lstfold.c			\
			  ft_strrev.c			\
			  ft_realloc.c			\
			  ft_list_sort.c		\
			  ft_deltab.c			\
			  ft_strjoin_free.c		\
			  ft_sqrt.c				\
			  ft_itoa_base.c		\
			  ft_nb_digits.c		\
			  ft_power.c			\
			  ft_max.c				\
			  ft_ultoa_base.c		\
			  ft_dtoa.c				\
			  ft_strfindchar.c		\
			  ft_ldpow.c			\
			  ft_ullpow.c			\
			  ft_char_size_utf8.c	\
			  ft_strlenw.c			\
			  ft_printf/ft_printf.c								\
			  ft_printf/print.c									\
			  ft_printf/ft_putldnbr_base_buffer.c				\
			  ft_printf/ft_putullnbr_base_buffer.c				\
			  ft_printf/ft_putcharw_buffer.c					\
			  ft_printf/printers/string.c						\
			  ft_printf/printers/lstring.c						\
			  ft_printf/printers/pointer.c						\
			  ft_printf/printers/character.c					\
			  ft_printf/printers/generic_decimal.c				\
			  ft_printf/printers/double.c						\
			  ft_printf/printers/double_utils.c					\
			  ft_printf/printers/none.c							\
			  ft_printf/printers/generic_number_utils.c			\
			  ft_printf/printers/generic_number_padding.c		\
			  ft_printf/modifiers/apply_modifiers.c				\
			  ft_printf/modifiers/h.c							\
			  ft_printf/modifiers/l.c							\
			  ft_printf/modifiers/l_cap.c						\
			  ft_printf/modifiers/z.c							\
			  ft_printf/modifiers/j.c							\
			  ft_printf/modifiers/modifiers.c					\
			  ft_printf/flags/flags.c							\
			  ft_printf/flags/minus.c							\
			  ft_printf/flags/plus.c							\
			  ft_printf/flags/zero.c							\
			  ft_printf/flags/space.c							\
			  ft_printf/flags/alternate.c						\
			  ft_printf/conversion.c							\
			  ft_printf/format.c								\
			  ft_printf/buffer.c								\
			  ft_put_tab.c		\
			  ft_atoi_base.c	\
			  get_next_line.c	\
			  ft_strndup.c		\
			  ft_insert_free.c	\
			  ft_del_char.c		\
			  ft_delelt.c		\
			  file_type.c		\
			  ft_listtotab.c	\
			  ft_lstlen.c		\
			  ft_quicksort.c	\
			  ft_match.c

SRCDIR  :=      src
OBJDIR  :=      obj
DEPDIR  :=      dep
INCDIR  :=      inc
LIBDIR  :=      lib

# File used as a command output buffer
TMP             :=      .tmp.txt
#
## *LOCA is the list of all subdirectory in a directory
SRCLOCA	:=      $(shell find $(SRCDIR) -type d)
OBJLOCA	:=      $(subst $(SRCDIR), $(OBJDIR), $(SRCLOCA))
DEPLOCA	:=      $(subst $(SRCDIR), $(DEPDIR), $(SRCLOCA))

OBJ		:=      $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEP		:=      $(addprefix $(DEPDIR)/, $(SRC:.c=.d))
SRC		:=      $(addprefix $(SRCDIR)/, $(SRC))

#### LIBRARY ####
include include.mk

#### COMPILER ####
CC              ?=      cc

INCFLAG := -I $(INCDIR)
STDFLAG ?=      -std=c99
WFLAGS  ?=      -Wall -Wextra -Werror
CFLAGS  =       $(WFLAGS) $(INCFLAG) $(STDFLAG)

DEPGEN  :=      $(CC)
DEPFLAG :=      -MM $(INCFLAG)

LD		:=      $(CC)
LDFLAG	:=      $(LIB_LINK)

# Fill the variable if the command exist, note &> does not work
CLANG_INSTALLED := $(shell which clang > /dev/null 2> /dev/null && echo yes)

#############################
#          COLORS           #
#############################
ifdef TERM
	RED             :=      "\033[1;31m"
	GREEN           :=      "\033[0;32m"
	BGREEN          :=      "\033[1;32m"
	BLUE            :=      "\033[0;34m"
	YELLOW          :=      "\033[0;33m"
	PURPLE          :=      "\033[0;35m"
	CYAN            :=      "\033[0;36m"
	GREY            :=      "\033[0;37m"
	# When printed reset the color
	COLRESET        :=      "\033[0m"
endif

COMPCOLOR       :=      $(GREEN)
LINKCOLOR       :=      $(PURPLE)
ONGOINGCOL      :=      $(YELLOW)
KOCOLOR         :=      $(RED)
RMCOLOR         :=      $(GREY)

MOVELINE        :=      "\033[1A"
CLEARLINE       :=      "\033[K"

#############################
#           RULES           #
#############################
#### COMPILE ####
# Standard rule used when just calling $> make
all:            $(NAME)

# Program linkage
$(NAME):        $(OBJ)
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"   : "$@$(MOVELINE)
	@ ar rcs $(NAME) $(OBJ)  &> $(TMP) && \
		(echo $(CLEARLINE)$(LINKCOLOR)[$(NAME)]$(COLRESET)"     : created"  ; \
		cat $(TMP) | sed -e "s/^/    /g" ; rm $(TMP)) || \
		(echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"    : linkage fail" ; \
		cat $(TMP) | sed -e "s/^/    /g" ; rm $(TMP) ; exit 1)

# Compilation and .d generation
$(OBJDIR)/%.o:          $(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"   : "$@$(MOVELINE)
	@ $(CC) -c $< $(CFLAGS) -o  $@ &> $(TMP) && \
		(echo $(CLEARLINE)$(COMPCOLOR)[OK]$(COLRESET)"  : "$@ ; \
		cat $(TMP) | sed -e "s/^/    /g") || \
		(echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"    : "$@ ; \
		cat $(TMP) | sed -e "s/^/    /g" ; rm $(TMP) ; exit 1)
	@ $(DEPGEN) -c $< $(DEPFLAG) -MQ $@ \
		> $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))


# Dir created to store .d and .o
$(OBJDIR):
	@ mkdir -p $(OBJLOCA)
$(DEPDIR):
	@ mkdir -p $(DEPLOCA)

# Recompile with as much warning as possible
warn:   WFLAGS := -Wall -Wextra -ansi -Wpedantic -Wno-vla
# If clang is installed also add this exclusive warning
ifdef CLANG_INSTALLED
warn:   CC := clang
warn:   WFLAGS += -Weverything
endif
warn:   lre

#### FORBIDEN FUNCTION ####
# Check forbiden funcion call
# All functions listed in .function_whitelist.txt are authorised
ffcheck:        $(NAME)
	@ nm -u $(NAME) | \
		sed -e 's/^\s*U\s//g' | grep -Ev '^\s*w\s|^__|dyld_stub_binder' | \
		grep -Ev \
		`cat .function_whitelist.txt | \
		sed -e 's/^/\^_?/g' | sed -e 's/$$/|/g' | \
		tr -d '\n' | sed 's/|$$//g'` &> $(TMP) ; \
		wc -l < $(TMP) | grep -e '^\s*\0$$' &> /dev/null && \
		echo $(BGREEN)[func]$(COLRESET)"        : no forbiden functions found" || \
		(echo $(RED)[func]$(COLRESET)"  : forbiden functions found" ; \
		cat $(TMP) | sed -e "s/^/    /g" ; rm $(TMP))

#### NORM ####
norm:
	@ norminette $(SRC) $(INCDIR) | \
		(! grep -E -B 1 "(^Warning|^Error)" &> $(TMP)) && \
		echo $(CYAN)[NORM]$(COLRESET)"  : pass, it's ok for now" || \
		(echo $(RED)[NORM]$(COLRESET)"  : you failed miserably !" ; \
		cat $(TMP) | sed -e "s/^/    /g" ; rm $(TMP))

sure: warn ffcheck norm

#### DEBUGING ####
# Change warning flag to debug and local recompile
debug:  WFLAGS := -g -ggdb
debug:  all

rdebug: WFLAGS := -g -ggdb
rdebug: lre

#### TESTS ####
# Use when you have some error and just want to rest
test:   WFLAGS :=
test:   all

# Test with everything recompile
rtest:  WFLAGS :=
rtest:  lre

#### LOCAL (Don't recompile lib) ####
lclean:
	@ rm -r $(OBJDIR) &> /dev/null && \
		echo $(RMCOLOR)[CLR]$(COLRESET)"        :" obj ; (exit 0)
	@ rm -r $(DEPDIR) &> /dev/null && \
		echo $(RMCOLOR)[CLR]$(COLRESET)"        :" dep ; (exit 0)

lfclean: lclean
	@ rm $(NAME) &> /dev/null && \
		echo $(RMCOLOR)[CLR]$(COLRESET)"        :" $(NAME) ; (exit 0)

lre: lfclean all

#### MANDATORY ####
clean: lclean
	@ rm -f $(TMP)

fclean:	lfclean

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
