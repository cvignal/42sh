# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 17:23:35 by fstadelw          #+#    #+#              #
#    Updated: 2018/12/03 10:36:47 by cvignal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT		:=	libft.a

LIBFT_PATH	?=	.

LIBFT_LINK	:= -L $(LIBFT_PATH) -l ft
LIBFT_INC	:= -I $(LIBFT_PATH)/includes

ifndef LIB_LINK
LIB_LINK	:=
LIB_INC		:=
endif

LIB_LINK	+= $(LIBFT_LINK)
LIB_INC		+= $(LIBFT_INC)
