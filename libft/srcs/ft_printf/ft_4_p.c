/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_4_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:42:22 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

void		ft_4_p(t_op *op, va_list ap)
{
	char			*base;
	unsigned long	tmp;

	base = "0123456789abcdef";
	tmp = va_arg(ap, long long);
	if (tmp == 0 && op->preci == 0)
		op->buffer = ft_strdup("0x");
	else
	{
		op->buffer = ft_itoa_p_base(tmp, base);
		op->buffer = ft_strfjoin("0x", op->buffer, 2);
	}
	if (op->preci != -1 || op->width != -1)
		ft_set_flag(op);
	else
		op->rprint = ft_strdup(op->buffer);
	ft_display(op);
}
