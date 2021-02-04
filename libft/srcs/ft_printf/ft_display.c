/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:01:21 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:29:00 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

void		ft_display(t_op *op)
{
	if (op->rprint == NULL)
	{
		ft_putstr("(null)");
		op->size += 6;
	}
	else if (op->rprint[0] == '\0' && op->converter == 'c')
	{
		op->size++;
		ft_putchar('\0');
	}
	else if (op->rprint)
	{
		ft_putstr(op->rprint);
		op->size += ft_strlen(op->rprint);
	}
	ft_delete(&op->buffer);
	ft_delete(&op->rprint);
}
