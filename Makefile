# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/11 22:50:24 by sofiahechai       #+#    #+#              #
#    Updated: 2021/03/12 16:32:22 by sohechai         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME			=		minishell

INCLUDE			=		includes

HEADERS			=		includes/minishell.h

CC				=		gcc

CFLAGS 			= 		-Wall -Wextra -Werror -g3 #-fsanitize=address

SRC				=		./srcs/main.c \
						./srcs/cmd_func/ft_execbuiltin.c \
						./srcs/cmd_func/ft_cd.c \
						./srcs/cmd_func/ft_pwd.c \
						./srcs/cmd_func/ft_env.c \
						./srcs/cmd_func/ft_echo.c \
						./srcs/cmd_func/ft_unset.c \
						./srcs/cmd_func/ft_export.c \
						./srcs/cmd_func/ft_exit.c \
						./srcs/cmd_func/ft_simplecmd.c \
						./srcs/cmd_func/ft_pipecmd.c \
						./srcs/parsing/ft_check_character.c \
						./srcs/parsing/ft_check_pipe.c \
						./srcs/parsing/check_after.c \
						./srcs/parsing/check_redirection.c \
						./srcs/parsing/ft_parsing.c \
						./srcs/parsing/ft_utils.c \
						./srcs/parsing/print_prompt_waiting.c \
						./srcs/parsing/tools_parsing.c \
						./srcs/parsing/reco_env.c \
						./srcs/parsing/remove_quote.c \
						./srcs/parsing/change_char_in_dquote.c \
						./srcs/parsing/env_tools.c \
						./srcs/tools/ft_subredir.c \
						./srcs/tools/ft_getabsolutepath.c \
						./srcs/tools/ft_builtin.c \
						./srcs/tools/ft_handlesignal.c \
						./srcs/tools/ft_getenv.c \
						./srcs/tools/ft_initstruct.c \
						./srcs/tools/ft_copytab.c \
						./srcs/tools/ft_copyenvp.c \
						./srcs/tools/ft_free.c \
						./srcs/tools/ft_checkvar.c \
						./srcs/tools/ft_strtokk.c \
						./srcs/tools/ft_sortenv.c \
						./srcs/tools/ft_redirection.c \
						./srcs/tools/option.c \
						./srcs/tools/ft_checkredirection.c \
						./srcs/tools/ft_execpipe.c \
						./srcs/tools/ft_redirectinfile.c \
						./srcs/tools/ft_leftredirection.c \
						./srcs/tools/redirection_tools.c \
						./srcs/tools/ft_getredirofnewfd.c \

OBJS			= 		$(SRC:.c=.o)

LIB 			= 		libft/libft.a

all				: 		$(NAME)

$(NAME)		: $(OBJS)
		@make -C libft
		@$(CC) $(CFLAGS) $(OBJS) -I $(HEADERS) $(LIB) -o $(NAME)

%.o: %.c $(HEADERS)
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

		@echo "\033[34m$(NAME): Loading... \033[0m"

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
