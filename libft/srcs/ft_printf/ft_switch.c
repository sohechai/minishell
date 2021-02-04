/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_switch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:59:38 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:30:45 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

void	ft_switch(t_op *op, va_list ap)
{
	if (op->converter == 's')
	{
		ft_4_alpha(op, ap);
	}
	else if (op->converter == 'c' || op->converter == '%')
		ft_4_c(op, ap);
	if (op->converter == 'd' || op->converter == 'i')
		ft_4_di(op, ap);
	else if (op->converter == 'p')
		ft_4_p(op, ap);
	else if (op->converter == 'x' || op->converter == 'X')
		ft_4_x(op, ap);
	else if (op->converter == 'u')
		ft_4_u(op, ap);
}
