/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:32:45 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

char		*ft_insert(char *src, char *insered, size_t n, int len)
{
	char	*dest;

	dest = ft_strndup(src, n);
	dest = ft_strfjoin(dest, insered, 1);
	dest = ft_strfjoin(dest, src + n + len, 1);
	ft_delete(&src);
	return (dest);
}
