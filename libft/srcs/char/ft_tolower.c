/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:52:29 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:27:03 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int		ft_tolower(int c)
{
	if (65 <= c && c <= 90)
		c = c + 32;
	return (c);
}
