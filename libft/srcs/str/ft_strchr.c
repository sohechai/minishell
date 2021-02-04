/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 10:13:16 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/22 09:19:03 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	if (c == '\0')
		return (0);
	if (c == '\0' && *str == '\0')
		return ((char*)str);
	while (str[i])
	{
		if (str[i] == '\0')
			return (0);
		if (str[i] == c)
			return ((char*)str);
		i++;
	}
	if (str[i] == c)
		return ((char*)str);
	return (0);
}
