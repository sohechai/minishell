# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurbuche <aurbuche@student.le-101.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 10:26:14 by aurbuche          #+#    #+#              #
#    Updated: 2020/03/12 13:17:40 by aurbuche         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS_PRINTF		=		ft_printf.c ft_change.c ft_insert.c ft_is.c ft_switch.c\
						ft_4_digit.c ft_display.c ft_set_flag.c ft_set_precision.c\
						ft_4_alpha.c ft_set_field.c ft_ctos.c ft_write_til.c\
						ft_4_x.c ft_4_alpha.c ft_4_p.c ft_4_c.c\
						ft_set_preci_field.c ft_all_to_zero.c ft_find_converter.c\
						ft_init_struct.c ft_insert_stars.c ft_check_error.c ft_free_struct.c

SRCS_PATH		=	./

SRCS 			=	$(SRC_PATH), $(SRCS_PRINTF)

OBJ_NAME		=	${SRCS_PRINTF:.c=.o}

OBJ				=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))

OBJ_PATH		=	obj/

NAME 			=	libftprintf.a

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -g3

RM				=	rm -rf

HEADER			=	./libftprintf.h ./libft/libft.h

all : compile_libft $(OBJ_PATH) ${NAME}
	
compile_libft: 
				@make -C libft NAME=../libftprintf.a

$(NAME) : $(OBJ) $(HEADER)
				@echo "\033[0m"
				@ar rcus $(NAME) $(OBJ)
				@echo "\033[0m"
				@echo "\033[38;2;0;128;0mDone"

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c $(HEADER) Makefile
				@${CC} ${CFLAGS}  -c $< -o $@
				@echo "\033[38;2;250;240;197mCompiling objects file...$<"
				@echo "\033[38;2;0;128;0mDone"

$(OBJ_PATH):
				@mkdir -p obj/ 2> /dev/null
				@mkdir -p obj/libft 2> /dev/null

clean :
				@${RM} ${OBJ}
				@${RM} libft/obj
				@echo "\033[38;2;165;38;10mDeleting objects file...\t\t\033[38;2;0;128;0mDONE\033[0m"

fclean :		clean
				@${RM} ${NAME}
				@${RM} libft/libft.a
				@${RM} obj/
				@${RM} a.out
				@echo "\033[38;2;165;38;10mDeleting libft.a...\t\t\t\033[38;2;0;128;0mDONE\033[0m"
				@echo "\033[38;2;165;38;10mDeleting libtprintf.a...\t\t\033[38;2;0;128;0mDONE\033[0m"
				
re :			fclean all
.PHONY :		all clean fclean re