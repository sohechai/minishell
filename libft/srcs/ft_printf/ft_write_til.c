/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_til.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:20:37 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:30:48 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

void		ft_write_til_percent(const char *fmt, size_t i)
{
	size_t	n;

	n = 0;
	while (n < i)
	{
		ft_putchar(fmt[n]);
		n++;
	}
}
