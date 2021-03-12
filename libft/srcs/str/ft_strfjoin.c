/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 09:08:26 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char			*ft_strfjoin(char *s1, char *s2, int free)
{
	char	*str;

	if (!(str = ft_strjoin(s1, s2)))
		return (0);
	if (free == 1)
		ft_delete(&s1);
	else if (free == 2)
		ft_delete(&s2);
	else if (free == 3)
	{
		ft_delete(&s1);
		ft_delete(&s2);
	}
	return (str);
}
