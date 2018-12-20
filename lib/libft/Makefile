# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gchainet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 13:58:37 by gchainet          #+#    #+#              #
#    Updated: 2018/12/19 18:22:05 by gchainet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	sources/ft_putchar.c								\
			sources/ft_putcharw.c								\
			sources/ft_strcat.c									\
			sources/ft_strcmp.c									\
			sources/ft_strcpy.c									\
			sources/ft_strlcat.c								\
			sources/ft_strncat.c								\
			sources/ft_strncmp.c								\
			sources/ft_strncpy.c								\
			sources/ft_strstr.c									\
			sources/ft_bzero.c									\
			sources/ft_char_size_utf8.c							\
			sources/ft_memset.c									\
			sources/ft_memcpy.c									\
			sources/ft_memmove.c								\
			sources/ft_memchr.c									\
			sources/ft_memcmp.c									\
			sources/ft_strlen.c									\
			sources/ft_strlenw.c								\
			sources/ft_strdup.c									\
			sources/ft_strchr.c									\
			sources/ft_strrchr.c								\
			sources/ft_strnstr.c								\
			sources/ft_atoi.c									\
			sources/ft_isalpha.c								\
			sources/ft_isdigit.c								\
			sources/ft_isalnum.c								\
			sources/ft_isascii.c								\
			sources/ft_isprint.c								\
			sources/ft_toupper.c								\
			sources/ft_tolower.c								\
			sources/ft_memalloc.c								\
			sources/ft_memdel.c									\
			sources/ft_nbrlen.c									\
			sources/ft_snbrlen.c								\
			sources/ft_strnew.c									\
			sources/ft_strdel.c									\
			sources/ft_strclr.c									\
			sources/ft_striter.c								\
			sources/ft_striteri.c								\
			sources/ft_strmap.c									\
			sources/ft_strmapi.c								\
			sources/ft_strequ.c									\
			sources/ft_strnequ.c								\
			sources/ft_strsub.c									\
			sources/ft_strjoin.c								\
			sources/ft_strjoin_free.c								\
			sources/ft_insert_free.c							\
			sources/ft_strtrim.c								\
			sources/ft_strsplit.c								\
			sources/ft_itoa.c									\
			sources/ft_putstr.c									\
			sources/ft_putendl.c								\
			sources/ft_putnbr.c									\
			sources/ft_putchar_fd.c								\
			sources/ft_putstr_fd.c								\
			sources/ft_putendl_fd.c								\
			sources/ft_putnbr_fd.c								\
			sources/ft_memccpy.c								\
			sources/ft_lstnew.c									\
			sources/ft_lstdelone.c								\
			sources/ft_lstdel.c									\
			sources/ft_lstadd.c									\
			sources/ft_lstaddend.c								\
			sources/ft_lstiter.c								\
			sources/ft_lstmap.c									\
			sources/ft_realloc.c								\
			sources/ft_putnbr_base.c							\
			sources/ft_putunbr.c								\
			sources/ft_ullpow.c									\
			sources/ft_ldpow.c									\
			sources/ft_printf/ft_printf.c						\
			sources/ft_printf/ft_dprintf.c						\
			sources/ft_printf/print.c							\
			sources/ft_printf/ft_putldnbr_base_buffer.c			\
			sources/ft_printf/ft_putullnbr_base_buffer.c		\
			sources/ft_printf/ft_putcharw_buffer.c				\
			sources/ft_printf/printers/string.c					\
			sources/ft_printf/printers/lstring.c				\
			sources/ft_printf/printers/pointer.c				\
			sources/ft_printf/printers/character.c				\
			sources/ft_printf/printers/generic_decimal.c		\
			sources/ft_printf/printers/double.c					\
			sources/ft_printf/printers/double_utils.c			\
			sources/ft_printf/printers/none.c					\
			sources/ft_printf/printers/generic_number_utils.c	\
			sources/ft_printf/printers/generic_number_padding.c	\
			sources/ft_printf/modifiers/apply_modifiers.c		\
			sources/ft_printf/modifiers/h.c						\
			sources/ft_printf/modifiers/l.c						\
			sources/ft_printf/modifiers/l_cap.c					\
			sources/ft_printf/modifiers/z.c						\
			sources/ft_printf/modifiers/j.c						\
			sources/ft_printf/modifiers/modifiers.c				\
			sources/ft_printf/flags/flags.c						\
			sources/ft_printf/flags/minus.c						\
			sources/ft_printf/flags/plus.c						\
			sources/ft_printf/flags/zero.c						\
			sources/ft_printf/flags/space.c						\
			sources/ft_printf/flags/alternate.c					\
			sources/ft_printf/conversion.c						\
			sources/ft_printf/format.c							\
			sources/ft_printf/buffer.c							\
			sources/get_next_line.c
	
HDR		=	includes

OBJ		=	$(SRC:.c=.o)

NAME	=	libft.a

$(NAME):	$(OBJ)
	ar rcs $(NAME) $(OBJ)
	ranlib $(NAME)

%.o:	%.c
	cc -g -Wall -Wextra -Werror -I $(HDR) -c $< -o $@

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean $(NAME)

.PHONY: clean fclean re
