/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_4_digit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 16:47:27 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:29:10 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

void		ft_4_u(t_op *op, va_list ap)
{
	char	*base;
	size_t	i;

	base = "0123456789";
	i = va_arg(ap, unsigned int);
	if (i == 0 && op->preci == 0)
		op->buffer = ft_strdup("");
	else
		op->buffer = ft_itoa_base(i, base);
	if (op->preci == 0 && op->width == 0)
		op->rprint = ft_strdup(op->buffer);
	else if ((op->preci != -1 || op->width != -1))
		ft_set_flag(op);
	else
		op->rprint = ft_strdup(op->buffer);
	ft_display(op);
}

void		ft_di2(t_op *op, va_list ap)
{
	int		i;

	i = va_arg(ap, int);
	if (i < 0 && i != -2147483648 && (op->preci > 0 || op->zero))
	{
		i = -i;
		op->neg = 1;
		op->buffer = ft_itoa(i);
	}
	else if (i == -2147483648 && (op->preci > 0 || op->width > 0))
	{
		op->buffer = ft_strdup("2147483648");
		op->neg = 1;
	}
	else if (i == 0 && ((op->width > 0 && !op->is_a_negative_width)
		|| (op->preci == 0)))
	{
		if (op->width > 0 && !op->is_a_negative_width && op->preci != 0)
			op->buffer = ft_strdup("0");
		else if (op->preci == 0 && i == 0)
			op->buffer = ft_strdup("");
	}
	else
		op->buffer = ft_itoa(i);
}

void		ft_4_di(t_op *op, va_list ap)
{
	ft_di2(op, ap);
	if (op->width < 0 && op->width != -1)
	{
		op->is_a_negative_width = 1;
		op->width = -op->width;
		op->zero = 0;
	}
	if (op->preci == 0 && (op->width == 0 || op->width == -1))
	{
		if (ft_atoi(op->buffer) == 0)
			op->rprint = ft_strdup("");
		else
			op->rprint = ft_strdup(op->buffer);
	}
	else if (op->preci != -1 || op->width != -1)
		ft_set_flag(op);
	else
		op->rprint = ft_strdup(op->buffer);
	if (op->neg)
		op->rprint = ft_strfjoin("-", op->rprint, 2);
	ft_display(op);
}
