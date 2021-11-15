# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 17:04:06 by kennahi           #+#    #+#              #
#    Updated: 2021/05/07 13:36:10 by kennahi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = libft/ft_atoi.c\
	  libft/ft_split.c\
	  libft/ft_strncmp.c\
	  libft/ft_putchar_fd.c\
	  libft/ft_putstr_fd.c\
	  libft/ft_memset.c\
	  getnextline/get_next_line.c\
	  getnextline/get_next_line_utils.c\
	  cub3D.c\
	  functions.c\
	  functions2.c\
	  map_parsing.c\
	  map_checker.c\
	  parsing.c\
	  errors.c\
	  spawning.c\
	  sprite.c\
	  drawing.c\
	  bmp.c\
	  keys.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -rf $(OBJ) $(OBJb)

fclean: clean
	@rm -rf $(NAME)

re: fclean all