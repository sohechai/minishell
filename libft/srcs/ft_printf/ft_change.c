/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:50:08 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:29:02 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

void			ft_change(t_op *op, char **str, size_t i, va_list ap)
{
	char	*tmp;

	tmp = NULL;
	while ((*str)[i] && !ft_is_converter((*str)[i]))
	{
		if ((*str)[i] == '*' && op->percent)
		{
			tmp = ft_itoa(va_arg(ap, int));
			*str = ft_insert(*str, tmp, i, 1);
			ft_delete(&tmp);
		}
		i++;
	}
}
