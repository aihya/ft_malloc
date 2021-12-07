# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/17 14:20:21 by aihya             #+#    #+#              #
#    Updated: 2021/12/07 18:56:47 by aihya            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC_NAME =	all.c\
			malloc.c \
			free.c \
			realloc.c \
			reallocf.c \
			calloc.c \
			tools.c \
			alloc_block.c \
			alloc_large.c \
			alloc_zone.c \
			best_fit.c \
			show_mem.c \
			show_mem_utils.c \
			corruption.c \
			search.c \
			defragement.c \
			realloc_utils.c \
			

OBJ_NAME =	$(SRC_NAME:.c=.o)

SRC_PATH =	src/
OBJ_PATH =	obj/

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

CFLAGS	=	-Wall -Werror -Wextra -g
INCLUDE	=	-Iinclude -Ilibft/include
DEPS 	=	./include/ft_malloc.h
LIBFT	=	-Llibft -lft

all : libft_all $(NAME)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(DEPS)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

libft_all :
	make -C libft

$(NAME) : $(OBJ)
	gcc -shared $(LIBFT) $(OBJ) -o $(NAME)
	ln -s $(NAME) libft_malloc.so 2> /dev/null || true

clean :
	make -C libft clean
	/bin/rm -rf $(OBJ_PATH)

fclean : clean
	make -C libft fclean
	/bin/rm -rf libft_malloc.so
	/bin/rm -rf $(NAME)

re : fclean all
