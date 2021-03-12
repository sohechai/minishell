/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_p_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 11:24:01 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char		*ft_itoa_p_base(unsigned long n, char *base)
{
	static char	buf[18];
	int			i;
	int			len;

	len = ft_strlen(base);
	i = 16;
	while (1)
	{
		buf[i--] = base[n % len];
		n /= len;
		if (n == 0)
			break ;
	}
	return (ft_strdup(buf + 1 + i));
}
