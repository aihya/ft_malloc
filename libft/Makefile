# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/17 14:47:46 by aihya             #+#    #+#              #
#    Updated: 2021/09/23 11:57:27 by aihya            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = libft.a

SRC_NAME =	ft_putaddr.c \
			ft_putchar.c \
			ft_putendl.c \
			ft_putstr.c \
			ft_putnbr.c \
			ft_memcpy.c \
			ft_bzero.c \
			ft_memset.c

OBJ_NAME =	$(SRC_NAME:.c=.o)

SRC_PATH =	src/
OBJ_PATH =	obj/

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

CFLAGS	=	-Wall -Werror -Wextra
INCLUDE	=	-Iinclude
DEPS	=	./include/libft.h

all : $(NAME)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(DEPS)
	@mkdir $(OBJ_PATH) 2>/dev/null || true
	gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(NAME) : $(OBJ)
	ar rc $@ $^
	ranlib $@

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all