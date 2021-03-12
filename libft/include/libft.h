/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:27:42 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_H
# define _LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libftprintf.h"

size_t			get_next_line(int fd, char **line);
int				ft_atoi(const char *str);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_itoa(int n);
char			*ft_itoa_base(unsigned int n, char *base);
char			*ft_itoa_p_base(unsigned long n, char *base);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s1);
char			*ft_strlcopy(char *dst, const char *src, size_t dstsize);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strfjoin(char *s1, char *s2, int ft_delete);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strncpy(char *dest, const char *src, unsigned int n);
char			*ft_strnstr(const char *stack, const char *ned, size_t len);
char			*ft_strndup(char *str, size_t n);
char			*ft_strtok(char *s, const char *charset);
char			*strnfdup(char *str, int len);
char			*ft_strnjoin(char *s1, char const *s2, size_t len);
char			**ft_split(char const *s, char c);
void			*ft_calloc(size_t count, size_t size);
void			ft_delete(char **ptr);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *b, size_t len);
void			ft_putchar_fd(char c, int fd);
void			ft_putchar(char c);
void			ft_putendl_fd(char *s, int fd);
void			ft_putendl(char *s);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr(int n);
void			ft_putstr_fd(char *s, int fd);
void			ft_putstr(char *s);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			ft_reset_tab(int *tab, int end);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *str);
size_t			ft_strnlen(const char *str, size_t n);
size_t			ft_cchr(char *str, size_t i, char c);
char			**ft_free_tab(char **tab);

#endif
