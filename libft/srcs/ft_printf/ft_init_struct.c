/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:23:00 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:29:47 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

t_op		*ft_init_struct(void)
{
	t_op	*option;

	if (!(option = (t_op *)malloc(sizeof(t_op))))
		return (NULL);
	ft_bzero(option, sizeof(t_op));
	option->percent = 1;
	return (option);
}
