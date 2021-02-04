# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 16:05:13 by sohechai          #+#    #+#              #
#    Updated: 2021/02/04 13:27:35 by sofiahechai      ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME			=		minishell

INCLUDE			=		includes

HEADERS			=		includes/minishell.h

CC				=		gcc

CFLAGS 			= 		-Wall -Wextra -Werror

SRC			=		./get_next_line.c \
					./get_next_line_utils.c \
					./srcs/main.c \
					./srcs/cmd_func/ft_execbuiltin.c \
					./srcs/cmd_func/ft_builtincd.c \
					./srcs/cmd_func/ft_builtinpwd.c \
					./srcs/cmd_func/ft_env.c \
					./srcs/tools/ft_getenv.c \
					./srcs/tools/ft_initstruct.c \
					./srcs/tools/ft_free.c \
					./srcs/tools/ft_copyenv.c \
					./srcs/tools/ft_strtokk.c \

OBJS			= 		$(SRC:.c=.o)

LIB 			= 		libft/libft.a

all				: 		$(NAME)

$(NAME)		: $(OBJS)
		@make -C libft
		@$(CC) $(CFLAGS) $(OBJS) -I $(HEADERS) $(LIB) -o $(NAME)

%.o: %.c $(HEADERS)
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

		@echo "\033[34m$(NAME): Loading... \033[0m"

submodule	:
			git submodule init && git submodule update

bonus		:		$(NAME)

clean		:
		@rm -f *.o srcs/*.o srcs/cmd_func/*.o srcs/tools/*.o
		@make clean -C libft
		@echo "\033[91m$(NAME):\033[31m Deleting *.o...\033[0m"
		@echo "\033[91m\n$(NAME)\033[31m is now clean\033[0m"
fclean		:		clean
		@rm -f $(NAME)
		@make fclean -C libft

re			:		fclean all

.PHONY: 	re fclean clean all