/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_converter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:14:53 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

int				ft_find_converter(char c, t_op *op)
{
	char	*converter;
	int		i;

	converter = "cspdiuxX%";
	i = 0;
	while (converter[i])
	{
		if (converter[i] == c)
		{
			op->converter = converter[i];
			return (1);
		}
		i++;
	}
	return (0);
}
