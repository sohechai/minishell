/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 09:50:38 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

int			ft_is_converter(char c)
{
	char	*converter;

	converter = "cspdiuxX%";
	while (*converter)
	{
		if (*converter == c)
			return (1);
		converter++;
	}
	return (0);
}

int			ft_is_flag(char c)
{
	if (c == '.' || c == '*' || c == '-' || c == '0')
	{
		return (1);
	}
	return (0);
}
