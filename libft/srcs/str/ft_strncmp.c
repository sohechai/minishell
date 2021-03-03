/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:53:50 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/03 14:37:36 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	unsigned const char	*str1;
	unsigned const char	*str2;

	str1 = (unsigned const char*)s1;
	str2 = (unsigned const char*)s2;
	i = 0;
	if (n <= 0)
		return (0);
	while (str1[i] == str2[i] && i < (n - 1) && str1[i] && str2[i])
		i++;
	return (str1[i] - str2[i]);
}
