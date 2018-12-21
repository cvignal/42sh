# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvignal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/20 14:14:18 by cvignal           #+#    #+#              #
#    Updated: 2018/12/21 11:08:46 by cvignal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include include.mk

SRC_DIR	= ./src
INC_DIR	= ./includes
OBJ_DIR	= ./obj


SRC			= ft_memset.c		\
			  ft_bzero.c		\
			  ft_memcpy.c		\
			  ft_memccpy.c		\
			  ft_memmove.c		\
			  ft_memchr.c		\
			  ft_memcmp.c		\
			  ft_strlen.c		\
			  ft_strdup.c		\
			  ft_strcpy.c		\
			  ft_strncpy.c		\
			  ft_strcat.c		\
			  ft_strncat.c		\
			  ft_strlcat.c		\
			  ft_strchr.c		\
			  ft_strrchr.c		\
			  ft_strstr.c		\
			  ft_strnstr.c		\
			  ft_strcmp.c		\
			  ft_strncmp.c		\
			  ft_atoi.c			\
			  ft_isalpha.c		\
			  ft_isdigit.c		\
			  ft_isalnum.c		\
			  ft_isascii.c		\
			  ft_isprint.c		\
			  ft_toupper.c		\
			  ft_tolower.c		\
			  ft_memalloc.c		\
			  ft_memdel.c		\
			  ft_strnew.c		\
			  ft_strdel.c		\
			  ft_strclr.c		\
			  ft_striter.c		\
			  ft_memalloc.c		\
			  ft_striteri.c		\
			  ft_strmap.c		\
			  ft_strmapi.c		\
			  ft_strequ.c		\
			  ft_strnequ.c		\
			  ft_strsub.c		\
			  ft_strjoin.c		\
			  ft_strtrim.c		\
			  ft_strsplit.c		\
			  ft_putstr.c		\
			  ft_putchar.c		\
			  ft_putendl.c		\
			  ft_putnbr.c		\
			  ft_putchar_fd.c	\
			  ft_putstr_fd.c	\
			  ft_putendl_fd.c	\
			  ft_putnbr_fd.c	\
			  ft_lstnew.c		\
			  ft_lstdelone.c	\
			  ft_lstdel.c		\
			  ft_lstadd.c		\
			  ft_lstiter.c		\
			  ft_lstmap.c		\
			  ft_lstapp.c		\
			  ft_strsplit_lst.c	\
			  ft_lstfold.c		\
			  ft_strrev.c		\
			  ft_realloc.c		\
			  ft_list_sort.c	\
			  ft_deltab.c		\
			  ft_strjoin_free.c	\
			  ft_sqrt.c			\
			  ft_itoa_base.c	\
			  ft_nb_digits.c	\
			  ft_power.c		\
			  ft_max.c			\
			  ft_ultoa_base.c	\
			  ft_dtoa.c			\
			  ft_strfindchar.c	\
			  ft_printf.c		\
			  tools_conv.c		\
			  ft_conv01.c		\
			  ft_sprintf.c		\
			  ft_conv02.c		\
			  ft_form00.c		\
			  ft_form01.c		\
			  ft_form02.c		\
			  ft_form03.c		\
			  ft_form04.c		\
			  ft_put_tab.c		\
			  ft_atoi_base.c	\
			  get_next_line.c	\
			  ft_strndup.c		\
			  ft_insert_free.c	\
			  ft_del_char.c		\
			  ft_delelt.c		\
			  file_type.c		\
			  ft_listtotab.c	\
			  ft_lstlen.c

OBJ			= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3

all: $(OBJ_DIR) $(LIBFT)
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(LIBFT_INC) -o $@ -c $<

$(LIBFT): $(OBJ)
	@ar rc $(LIBFT) $(OBJ)
	@ranlib $(LIBFT)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(LIBFT)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all clean fclean re
