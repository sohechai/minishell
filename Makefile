# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 16:05:13 by sohechai          #+#    #+#              #
#    Updated: 2021/02/16 21:12:15 by sofiahechai      ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME			=		minishell

INCLUDE			=		includes

HEADERS			=		includes/minishell.h

CC				=		gcc

CFLAGS 			= 		-Wall -Wextra -Werror

SRC			=		./srcs/main.c \
					./srcs/cmd_func/ft_execbuiltin.c \
					./srcs/cmd_func/ft_builtincd.c \
					./srcs/cmd_func/ft_builtinpwd.c \
					./srcs/cmd_func/ft_env.c \
					./srcs/cmd_func/ft_echo.c \
					./srcs/cmd_func/ft_simplecmd.c \
					./srcs/cmd_func/ft_unsetenv.c \
					./srcs/cmd_func/ft_exportenv.c \
					./srcs/parsing/ft_check_character.c \
					./srcs/parsing/ft_check_pipe.c \
					./srcs/parsing/ft_parsing.c \
					./srcs/parsing/ft_recover_cmd.c \
					./srcs/parsing/ft_utils.c \
					./srcs/parsing/print_prompt_waiting.c \
					./srcs/parsing/tools_parsing.c \
					./srcs/parsing/reco_env.c \
					./srcs/tools/ft_getenv.c \
					./srcs/tools/ft_initstruct.c \
					./srcs/tools/ft_free.c \
					./srcs/tools/ft_checkvar.c \
					./srcs/tools/ft_echoutils.c \
					./srcs/tools/ft_strtokk.c \
					./srcs/tools/ft_sortenv.c \
					./srcs/tools/option.c \
					./srcs/tools/ft_checkredirection.c \

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
		@rm -f *.o srcs/*.o srcs/cmd_func/*.o srcs/tools/*.o srcs/parsing/*.o
		@make clean -C libft
		@echo "\033[91m$(NAME):\033[31m Deleting *.o...\033[0m"
		@echo "\033[91m\n$(NAME)\033[31m is now clean\033[0m"
fclean		:		clean
		@rm -f $(NAME)
		@make fclean -C libft

re			:		fclean all


run		:	${NAME}
			@./${NAME}

.PHONY: 	re fclean clean all run