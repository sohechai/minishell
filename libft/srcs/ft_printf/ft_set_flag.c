/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 11:19:29 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

void		ft_set_flag(t_op *op)
{
	if (op->is_a_negative_width && op->is_a_negative_precision
		&& op->preci > op->width)
		op->width = op->preci;
	if (op->is_a_negative_precision && op->converter != 's')
		op->preci = -op->preci;
	if (op->width != -1 && op->preci == -1)
	{
		ft_set_field(op);
	}
	else if (op->preci != -1 && op->width == -1)
	{
		ft_set_precision(op);
	}
	else
	{
		if (op->preci < 0 && op->is_a_negative_width)
		{
			op->preci = -op->preci;
			if (op->preci > op->width)
				op->width = op->preci;
			op->preci = -1;
		}
		ft_set_preci_field(op);
	}
}
