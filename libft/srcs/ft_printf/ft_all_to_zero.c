/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_to_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:19:04 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:29:03 by aurelienbuc      ###   ########lyon.fr   */
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
