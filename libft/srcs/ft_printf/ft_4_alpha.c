/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_4_alpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:42:44 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:29:15 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

void		ft_alpha2(t_op *op, va_list ap)
{
	if (op->preci == 0)
	{
		va_arg(ap, void *);
		op->buffer = ft_strdup("");
	}
	else
		op->buffer = ft_strdup(va_arg(ap, char*));
	if (!op->buffer)
	{
		ft_delete(&op->buffer);
		op->buffer = ft_strdup("(null)");
	}
	else if (op->buffer[0] == '\0')
	{
		ft_delete(&op->buffer);
		op->buffer = ft_strdup("");
	}
}

void		ft_4_alpha(t_op *op, va_list ap)
{
	ft_alpha2(op, ap);
	if (op->preci == 0 && op->width == 0)
	{
		ft_delete(&op->buffer);
		op->buffer = ft_strdup("");
	}
	if ((op->preci != -1 || op->width != -1))
	{
		if (op->preci == 0 && op->width)
		{
			ft_delete(&op->buffer);
			op->buffer = ft_strdup("");
		}
		ft_set_flag(op);
	}
	else
		op->rprint = ft_strdup(op->buffer);
	ft_display(op);
}
