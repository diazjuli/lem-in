# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/15 19:22:08 by jdiaz             #+#    #+#              #
#    Updated: 2018/11/09 21:57:42 by jdiaz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

### PATH ###
SRCS_PATH = srcs/
OBJ_PATH  = obj/
LIBFT_PATH = libft/

FLAGS = -Wall -Werror -Wextra
INC = -I ./includes/ -I ./$(LIBFT_PATH)includes/

SRC = srcs/main.c srcs/read_file.c srcs/tools.c srcs/vertices.c \
	  srcs/edges.c srcs/path.c srcs/print.c srcs/free.c

OBJ = main.o read_file.o tools.o vertices.o \
	  edges.o path.o print.o free.o


all: $(NAME)

$(NAME):
	@make -C $(LIBFT_PATH)
	@gcc $(FLAGS) $(INC) -c $(SRC)
	@gcc -o $(NAME) $(OBJ) libft/libft.a
	@echo "Compiled $(NAME)"

clean:
	@make -C $(LIBFT_PATH)/ clean
	@/bin/rm -rf $(OBJ)
	@echo "Cleaned $(OBJ)"

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@/bin/rm -rf $(NAME)
	@echo "Cleaned $(NAME)"

re: fclean all

.PHONY: all, clean, fclean, re
