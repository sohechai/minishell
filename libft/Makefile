# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/10 15:28:27 by aurbuche          #+#    #+#              #
#    Updated: 2021/02/04 13:31:51 by sofiahechai      ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


SRCS_ALLOC		=	$(addprefix alloc/, ft_calloc.c ft_strdup.c ft_strndup.c\
					ft_substr.c)

SRCS_CHAR		=	$(addprefix char/, ft_isalnum.c ft_isalpha.c ft_isascii.c\
					ft_isdigit.c ft_isprint.c ft_tolower.c ft_toupper.c ft_cchr.c)

SRCS_CONVERT	=	$(addprefix convert/, ft_atoi.c ft_itoa.c ft_itoa_base.c\
					ft_itoa_p_base.c)

SRCS_DISPLAY	=	$(addprefix display/, ft_putchar.c ft_putchar_fd.c\
					ft_putendl_fd.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c\
					ft_putnbr.c ft_putendl.c)

SRCS_FREE		=	$(addprefix free/, ft_delete.c ft_free_tab.c ft_reset_tab.c)

SRCS_MEM		=	$(addprefix mem/, ft_bzero.c ft_memccpy.c ft_memchr.c\
					ft_memcmp.c ft_memcpy.c\
					ft_memmove.c ft_memset.c)

SRCS_STR		=	$(addprefix str/, ft_split.c ft_strchr.c ft_strcpy.c\
					ft_strfjoin.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c\
					ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnlen.c\
					ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_strcat.c\
					ft_strlcopy.c ft_strtok.c ft_strcmp)

SRCS_READ		=	$(addprefix read/, get_next_line.c)

SRCS_PRINTF		=		$(addprefix ft_printf/, ft_printf.c ft_change.c ft_insert.c\
						ft_is.c ft_switch.c ft_4_digit.c ft_display.c ft_set_flag.c\
						ft_set_precision.c ft_4_alpha.c ft_set_field.c ft_ctos.c\
						ft_write_til.c ft_4_x.c ft_4_alpha.c ft_4_p.c ft_4_c.c\
						ft_set_preci_field.c ft_all_to_zero.c ft_find_converter.c\
						ft_init_struct.c ft_insert_stars.c ft_check_error.c ft_free_struct.c)

SRCS_NAME			=	$(SRCS_ALLOC) $(SRCS_CHAR) $(SRCS_CONVERT) $(SRCS_DISPLAY) $(SRCS_FREE) $(SRCS_LIST) $(SRCS_MEM) $(SRCS_STR) $(SRCS_READ) $(SRCS_PRINTF)

HEADER				=	include/

SRC_PATH			=	srcs/

SRCS				=	$(addprefix $(SRC_PATH), $(SRCS_NAME))

OBJ_NAME			=	${SRCS_NAME:.c=.o}

OBJ_PATH			=	obj/

OBJ					=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))

NAME				=	libft.a

CC					=	cc

RM					=	rm -rf

FLAG				=	-Wall -Werror -Wextra -g3 #-fsanitize=address

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@ar rcs $(NAME) $(OBJ)
	@printf "	\033[2K\r\033[1;38;5;110mlibft\t:\t\033[0;38;5;121mUpdated\n\033[0m"

$(OBJ_PATH):
	@mkdir -p obj/ 2> /dev/null
	@mkdir -p obj/alloc 2> /dev/null
	@mkdir -p obj/char 2> /dev/null
	@mkdir -p obj/convert 2> /dev/null
	@mkdir -p obj/display 2> /dev/null
	@mkdir -p obj/ft_printf 2> /dev/null
	@mkdir -p obj/free 2> /dev/null
	@mkdir -p obj/mem 2> /dev/null
	@mkdir -p obj/str 2> /dev/null
	@mkdir -p obj/read 2> /dev/null

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER) Makefile
	@printf "\033[2K\r\033[0;31;5;110mCompiling...	\033[37m$<\033[36m \033[0m"
	@gcc $(FLAG) -g3 -I ${HEADER} -c $< -o $@

clean:
	@printf "\33[2K\r\033[0;31;5;110mDeleting libft srcs/	\033[37m"
	@sleep 0.5
	@printf "\33[2K\r\033[0;31;5;110mDeleting libft srcs/.	\033[37m"
	@sleep 0.5
	@printf "\33[2K\r\033[0;31;5;110mDeleting libft srcs/..	\033[37m"
	@sleep 0.5
	@printf "\33[2K\r\033[0;31;5;110mDeleting libft srcs/...	\033[37m"
	@sleep 0.5
	@${RM} ${OBJ_PATH}
	@printf "\33[2K\r\033[0;31;5;110mDeleted successfully!\n\033[0m"

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re