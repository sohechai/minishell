/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:54:19 by Tcurinie          #+#    #+#             */
/*   Updated: 2021/01/23 13:33:14 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>

# define ERROR -1
# define TRUE 1
# define FALSE 0
# define BUFFER_SIZE 1

/*
** 	Define_struct
*/

/*
**		Printf
*/

typedef struct			s_print
{
	void				(*tabfunction[9])(va_list q, char * w, int * e);
	char				tabindex[10];
	char				*flags;
	int					i;
	int					tmpindex;
	int					len;
}						t_print;

/*
**		GNL
*/

typedef struct			s_listgnl
{
	char				*content;
	int					fd;
	int					size;
	char				buff[BUFFER_SIZE + 1];
	struct s_listgnl	*before;
	struct s_listgnl	*next;
}						t_listgnl;

/*
**		Libft
*/

typedef struct			s_list
{
	void				*content;
	struct s_list		*next;
	struct s_list		*prev;
}						t_list;

/*
**		Char_functions
*/

int						ft_isalpha(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_isdigit(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
int						ft_putchar(char c);

/*
**		Str_functions
*/

int						ft_atoi(const char *str);
char					*ft_strchr(const char *s, int c);
char					*ft_substr(char const *s, unsigned int start, \
						size_t len);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strjoinfree(char *s1, char *s2, char *strfree);
char					*ft_strtrim(char const *s1, char const *set);
char					**ft_split(char const *s, char c);
char					**ft_split_cset(char const *s, char *set, int i);
char					*ft_itoa(int n);
char					*ft_itoa_base(int n, char *set);
char					*ft_utoa_base(unsigned long n, char *set);
char					*ft_strcat(char *dest, const char *src);
int						ft_strcmp(const char *str1, const char *str2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
void					ft_putstr(char *s);
char					*ft_strdup(const char *s1);
size_t					ft_strlen(const char *s);
char					*ft_strmapi(char const *s, char \
						(*f)(unsigned int, char));
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
char					**ft_free_split(char **strs, int k);
double					ft_atod(const char *s);
char					*ft_dtoa(long double nb);
int						ft_strisnum(char *str);

/*
**		Mem_functions
*/

void					ft_free2(void *str);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c, \
						size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_calloc(size_t count, size_t size);
void					*ft_realloc(void *ptr, size_t new_size);

/*
**		Fd_functions
*/

void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);

/*
**		Lst_fuctions
*/

t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **alst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **alst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/*
**		Ft_Printf
*/

char					*fill_alloc(char c, int j);
void					init_struct(t_print *base);
int						ft_printf(const char *src, ...);
int						is_minus(char *o_flags, int j);
char					*move_minus(char *str, int j);
char					*wi_nb(char *str, char *o_flags, int index, int zero);
char					*pre_nb(char *str, char *o_flags, int preci);
char					*minus_nb(char *str, char *o_flags, int preci);
void					ft_char(va_list my_list, char *o_flags, int *o_len);
void					ft_str(va_list my_list, char *o_flags, int *o_len);
void					ft_address(va_list my_list, char *o_flags, int *o_len);
void					ft_nbr(va_list my_list, char *o_flags, int *o_len);
void					ft_unsnbr(va_list my_list, char *o_flags, int *o_len);
void					ft_hexa(va_list my_list, char *o_flags, int *o_len);
void					ft_hexabig(va_list my_list, char *o_flags, int *o_len);
void					ft_percent(va_list my_list, char *o_flags, int *o_len);
int						findindex(char *tab, char element);
int						is_valid_type(char c, char *set);
char					*flags_formater(va_list my_list, char *o_flags);
int						ext_param(char *o_flags, char type);
int						ext_width(char *o_flags);
int						ext_zero(char *o_flags);
void					ft_putandfree(char *str, int *o_len);
int						ft_idontknow(char *o_flags, int j);
char					*wimin_adress(char *str, char *o_flags);

/*
**		GNL
*/

t_listgnl				*ft_lst_manage(t_listgnl *lst, int fd);
t_listgnl				*ft_lst_init(t_listgnl **alst, int fd);
char					*ft_strdup_gnl(char *s1);
int						strlen_gnl(const char *line, char chr);
char					*ft_strjoinfree_gnl(char *s1, char *s2);
int						get_next_line(int fd, char **line);
int						ft_write(char **line, t_listgnl *current);
int						ft_lstfreeone(t_listgnl *current, \
						t_listgnl **stock, int re);
int						ft_lstclear_gnl(t_listgnl **stock);
int						ft_read(t_listgnl *current, t_listgnl **stock);

#endif
