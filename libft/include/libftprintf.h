/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 10:30:24 by aurelienbuc       #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

/*
** --------------------------- External Headers ------------------------------
*/

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

/*
** -------------------------- Structure Definition ---------------------------
*/

typedef struct	s_option
{
	char			*buffer;
	char			*rprint;
	ssize_t			width;
	ssize_t			preci;
	char			converter;
	int				neg;
	size_t			size;
	size_t			percent;
	int				zero;
	int				is_a_negative_precision;
	int				is_a_negative_width;
}				t_op;

/*
** -------------------------- Function Definiton ----------------------------
*/

t_op			*ft_init_struct(void);
int				ft_check_error(const char *format, char **fmt);
int				ft_core_printf(char **fmt, size_t i, t_op *op, va_list ap);
int				ft_printf(const char *format, ...);
int				ft_4_digit2(t_op *option, int i);
int				ft_loop(char *fmt, size_t i, t_op *option, va_list ap);
int				ft_is_converter(char c);
int				ft_find_flag(char *str, size_t n, t_op *option);
int				ft_find_converter(char c, t_op *op);
int				ft_printf(const char *format, ...);
void			ft_switch(t_op *option, va_list ap);
void			ft_4_alpha(t_op *option, va_list ap);
void			ft_4_c(t_op *option, va_list ap);
void			ft_4_di(t_op *option, va_list ap);
void			ft_4_x(t_op *option, va_list ap);
void			ft_4_p(t_op *option, va_list ap);
void			ft_4_percent(t_op *option);
void			ft_4_u(t_op *option, va_list ap);
void			ft_all_to_zero(t_op *option);
void			ft_change(t_op *op, char **str, size_t i, va_list ap);
void			ft_display(t_op *option);
void			ft_free_struct(t_op *op, char *fmt);
void			ft_insert_stars(char **fmt, size_t i, t_op *op, va_list ap);
void			ft_set_flag(t_op *option);
void			ft_set_precision(t_op *option);
void			ft_set_preci_field(t_op *option);
void			ft_set_field(t_op *option);
void			ft_all_to_zero(t_op *option);
void			ft_write_til_percent(const char *fmt, size_t i);
char			*ft_ctos(char c);
char			*ft_insert(char *src, char *insered, size_t n, int len);
size_t			ft_size_field(t_op *option, char *str, size_t i);

#endif
