/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:46:23 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strndup(char *str, size_t n)
{
	char		*dst;
	size_t		i;

	i = 0;
	if (!(dst = (char*)malloc(sizeof(char) * (ft_strnlen(str, n) + 1))))
		return (NULL);
	while (n)
	{
		dst[i] = str[i];
		i++;
		n--;
	}
	dst[i] = '\0';
	return (dst);
}
