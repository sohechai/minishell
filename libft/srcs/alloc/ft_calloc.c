/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:33:28 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:27:16 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*d;

	if (!(ptr = malloc(size * count)))
		return (NULL);
	d = ptr;
	count *= size;
	while (count)
	{
		*d = 0;
		d++;
		count--;
	}
	return (ptr);
}
