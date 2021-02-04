/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:30:23 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:23:57 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (src == NULL && dst == NULL && n != 0)
		return (NULL);
	d = dst;
	s = src;
	while (n)
	{
		*d = *s;
		s++;
		d++;
		n--;
	}
	return (dst);
}
