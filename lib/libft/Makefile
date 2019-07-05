# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvignal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/07 16:39:44 by cvignal           #+#    #+#              #
#    Updated: 2019/07/05 16:27:26 by cvignal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= ft_memset.c										\
			  ft_bzero.c										\
			  ft_memcpy.c										\
			  ft_memccpy.c										\
			  ft_memmove.c										\
			  ft_memchr.c										\
			  ft_memcmp.c										\
			  ft_strlen.c										\
			  ft_strdup.c										\
			  ft_strcpy.c										\
			  ft_strncpy.c										\
			  ft_strcat.c										\
			  ft_strncat.c										\
			  ft_strlcat.c										\
			  ft_strchr.c										\
			  ft_strrchr.c										\
			  ft_strstr.c										\
			  ft_strnstr.c										\
			  ft_strcmp.c										\
			  ft_strncmp.c										\
			  ft_atoi.c											\
			  ft_isalpha.c										\
			  ft_isdigit.c										\
			  ft_isalnum.c										\
			  ft_isascii.c										\
			  ft_isprint.c										\
			  ft_toupper.c										\
			  ft_tolower.c										\
			  ft_memalloc.c										\
			  ft_memdel.c										\
			  ft_strnew.c										\
			  ft_strdel.c										\
			  ft_strclr.c										\
			  ft_striter.c										\
			  ft_memalloc.c										\
			  ft_striteri.c										\
			  ft_strmap.c										\
			  ft_strmapi.c										\
			  ft_strequ.c										\
			  ft_strnequ.c										\
			  ft_strsub.c										\
			  ft_strjoin.c										\
			  ft_strtrim.c										\
			  ft_strsplit.c										\
			  ft_putstr.c										\
			  ft_putchar.c										\
			  ft_putendl.c										\
			  ft_putnbr.c										\
			  ft_putchar_fd.c									\
			  ft_putstr_fd.c									\
			  ft_putendl_fd.c									\
			  ft_putnbr_fd.c									\
			  ft_lstnew.c										\
			  ft_lstdelone.c									\
			  ft_lstdel.c										\
			  ft_lstadd.c										\
			  ft_lstiter.c										\
			  ft_lstmap.c										\
			  ft_lstapp.c										\
			  ft_strsplit_lst.c									\
			  ft_lstfold.c										\
			  ft_strrev.c										\
			  ft_realloc.c										\
			  ft_list_sort.c									\
			  ft_deltab.c										\
			  ft_strjoin_free.c									\
			  ft_sqrt.c											\
			  ft_itoa_base.c									\
			  ft_nb_digits.c									\
			  ft_power.c										\
			  ft_max.c											\
			  ft_ultoa_base.c									\
			  ft_dtoa.c											\
			  ft_strfindchar.c									\
			  ft_ldpow.c										\
			  ft_ullpow.c										\
			  ft_char_size_utf8.c								\
			  ft_strlenw.c										\
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
			  ft_atoi_base.c									\
			  get_next_line.c									\
			  ft_strndup.c										\
			  ft_insert_free.c									\
			  ft_del_char.c										\
			  ft_delelt.c										\
			  file_type.c										\
			  ft_listtotab.c									\
			  ft_lstlen.c										\
			  ft_quicksort.c									\
			  ft_match.c										\
			  ft_bubblesort.c									\
			  ft_min.c											\
			  ft_abs.c											\
			  ft_strrstr.c										\
			  ft_arrayadd.c										\
			  ft_swap.c											\
			  ft_replace_str.c									\
			  ft_replace_all.c									\
			  ft_itoa.c											\
			  ft_arraymerge.c									\
			  ft_vswap.c										\
			  ft_quicksort.c									\
			  ft_strnchr.c

NAME		:=	libft.a

SRCDIR		:=	src
INCDIR		:=	inc
OBJDIR		:=	obj
DEPDIR		:=	dep

CC		:=	cc
AR			=	ar
DEPGEN		:=	cc
RANLIB		=	ranlib
RM		:=	rm -rf

CFLAGS		:=	-Wall -Werror -Wextra -ggdb
IFLAGS		:=	-I $(INCDIR)
DFLAGS		:=	-MM $(IFLAGS)

OBJ			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEP			:=	$(addprefix $(DEPDIR)/, $(SRC:.c=.d))
SRC			:=	$(addprefix $(SRCDIR)/, $(SRC))

SUBDIRS		:=	$(dir $(DEP)) $(dir $(OBJ))

$(NAME):	 make_dirs $(OBJ)
	$(AR) rc $(NAME) $(OBJ)
	$(RANLIB) $(NAME)


$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	$(DEPGEN) $(DFLAGS) -c $< -MQ $@ > $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

make_dirs:
	@mkdir -p $(SUBDIRS)

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
