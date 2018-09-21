# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdorner <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 08:56:20 by jdorner           #+#    #+#              #
#    Updated: 2018/07/25 13:20:23 by jdorner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
NAME = fdf
HEAD = fdf.h
SRC = 	main.c mouse.c keyboard.c gui.c drawline.c reader.c map.c render.c
OBJ = $(SRC:%.c=%.o)
GRA = -L -lmlx -framework OpenGL -framework AppKit
LIBFT = -L ./libft -l ft
GNL = ./get_next_line/get_next_line.c

# compiling
all: $(NAME)

$(NAME):
	make -C libft/
	@$(CC) -c $(SRC) $(GNL)
	@$(CC) $(LIBFT) -I $(HEADER) $(GRA) $(GNL) $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ) get_next_line.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all
