/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_4_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:20:05 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:29:07 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

void		ft_continue2(t_op *op, size_t i)
{
	if (i == 0 && op->preci == 0)
	{
		ft_delete(&op->buffer);
		op->buffer = ft_strdup("");
	}
	ft_set_flag(op);
}

void		ft_4_x(t_op *op, va_list ap)
{
	char	*base;
	size_t	i;

	base = "0123456789abcdef";
	if (op->converter == 'X')
		base = "0123456789ABCDEF";
	i = va_arg(ap, long long);
	op->buffer = ft_itoa_base(i, base);
	if ((op->preci == 0 && op->width == 0) ||
	(i == 0 && op->preci == 0 && op->width == -1))
	{
		if (i == 0)
			op->rprint = ft_strdup("");
		else
			op->rprint = ft_strdup(op->buffer);
	}
	else if (op->preci != -1 || op->width != -1)
	{
		ft_continue2(op, i);
	}
	else
		op->rprint = ft_strdup(op->buffer);
	ft_display(op);
}
