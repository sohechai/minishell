# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 16:05:13 by sohechai          #+#    #+#              #
#    Updated: 2021/02/01 16:54:46 by sohechai         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME 	=	minishell

HEADER 	=	./includes/minishell.h

SRC 	=	./srcs/main.c \
			./srcs/cmd_func/ft_execbuiltin.c \
			./srcs/tools/ft_getenv.c \
			./srcs/tools/ft_initstruct.c \
			./srcs/tools/ft_splits.c \

FLAGS 	=	-Wall -Wextra -Werror

OBJ		= 	$(SRC:.c=.o)

RM		=	rm -rf

CC		=	gcc
all: 		$(NAME)

$(NAME): 	$(OBJ)
			@$(MAKE)  -C ./libft
			@$(MAKE)  -C ./ft_printf
	 		@$(CC) $(FLAGS) -I includes -o $@ $^ ft_printf/libftprintf.a libft/libft.a -I $(HEADER) -L
	@echo " \033[2K\r\033[95m\n\n\n\n\n\n.\n.\n..\n...\n....\n....\n...\n..\n.\n.\033[0m"
	@echo " \033[2K\r\033[95m.\n.\n..\n...\n....\n....\n...\n..\n.\n.\033[0m"
	@echo "	\033[2K\r\033[95m\n$(NAME) is ready to be executed :)\n\033[0m"
	@echo "	\033[2K\r\033[95m\nTo start the game please type : ./cub3d and add a map file ending by '.cub' :\n\033[0m"


%.o: %.c 	@includes/minishell.h
	 		@$(CC) -I includes -o $@ -c $< $(FLAGS)

clean:
			@$(MAKE) clean -C libft
			@$(MAKE)  clean -C ./ft_printf
			@$(RM) $(OBJ)
	@echo " \033[2K\r\033[0;38;5;121m\n\n\n\n\n\n.\n.\n..\n...\n....\n....\n...\n..\n.\n.\033[0m"
	@echo " \033[2K\r\033[0;38;5;121m.\n.\n..\n...\n....\n....\n...\n..\n.\n.\033[0m"
	@echo "\033[2K\033[0;38;5;121m\n./$(NAME), *.o and *.a have been deleted\n\nFiles of $(NAME) are now clean :)\n"

fclean: 	clean
			@$(RM) $(NAME)
			@$(RM) libft/*.a

re: 		fclean all

.PHONY: 	re fclean clean all