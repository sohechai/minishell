/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_to_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:19:04 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

void	ft_all_to_zero(t_op *op)
{
	op->percent = 0;
	op->neg = 0;
	op->zero = 0;
	op->preci = -1;
	op->width = -1;
	op->converter = 0;
	op->is_a_negative_precision = 0;
	op->is_a_negative_width = 0;
}
