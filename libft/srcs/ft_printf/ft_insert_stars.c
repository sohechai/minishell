/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_stars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:32:28 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

void			ft_insert_stars(char **fmt, size_t i, t_op *op, va_list ap)
{
	while ((*fmt)[i])
	{
		if ((*fmt)[i] == '%' && !op->percent)
		{
			i++;
			op->percent = 1;
		}
		if (op->percent)
		{
			ft_change(op, (fmt), i, ap);
		}
		if (ft_find_converter((*fmt)[i], op) && op->percent)
		{
			op->percent = 0;
		}
		i++;
	}
}
