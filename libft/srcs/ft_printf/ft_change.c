/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:50:08 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
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
