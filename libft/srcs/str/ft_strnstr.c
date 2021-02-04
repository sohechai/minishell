/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:52:30 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:23:24 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strnstr(const char *haystack, const char *neddle, size_t len)
{
	int	i;
	int	j;
	int k;

	i = 0;
	if (neddle[0] == '\0')
		return ((char*)haystack);
	while (haystack[i] != '\0' && len > 0)
	{
		j = 0;
		k = len;
		while (haystack[i + j] == neddle[j] && k > 0)
		{
			if (neddle[j + 1] == '\0')
				return ((char*)haystack + i);
			j++;
			k--;
		}
		i++;
		len--;
	}
	return (0);
}
